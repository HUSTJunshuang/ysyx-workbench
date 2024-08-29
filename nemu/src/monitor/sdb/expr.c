/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <memory/paddr.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256,
  TK_EQ, TK_NEQ,
  TK_BAND, TK_BOR, TK_XOR,
  TK_LAND, TK_LOR,
  TK_REG, TK_PTR,
  TK_NEG, TK_NUM,
  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"([1-9])([0-9])*(UL)?", TK_NUM},
  {"0[xX][0-9a-fA-F]+", TK_NUM},
  {"0(UL)?", TK_NUM},
  {"\\$[$0-9a-z]*", TK_REG},
  {"\\+", '+'},         // plus
  {"-", '-'},           // minus
  {"\\*", '*'},         // multiply
  {"/", '/'},           // divide
  {"\%", '%'},          // mod
  {"\\(", '('},         // left bracket
  {"\\)", ')'},         // right bracket
  
  {"==", TK_EQ},        // equal
  {"!=", TK_NEQ},       // not equal
  {"&&", TK_LAND},      // logic and
  {"\\|\\|", TK_LOR},   // logic or
  {"&", TK_BAND},       // bit-wise and
  {"\\|", TK_BOR},      // bit-wise or
  {"\\^", TK_XOR},      // bit-wise xor
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[1024] __attribute__((used)) = {};
static word_t num_stack[1024] __attribute__((used)) = {};
static Token op_stack[1024] __attribute__((used)) = {};
static int num_ptr __attribute__((used)) = 0;
static int op_ptr __attribute__((used)) = 0;
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  if (e == NULL){
    return false;
  }
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        // Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
        //     i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        // use dup to avoid the bug caused by that string in tokens copied by strncpy have no '\0'
        char *match = strndup(substr_start, substr_len);
        switch (rules[i].token_type) {
          case TK_NOTYPE: break;
          case '-': {
            if (nr_token == 0 || (nr_token > 0 && ((tokens[nr_token - 1].type != ')') &&
                (tokens[nr_token - 1].type != TK_NUM)))) {
              tokens[nr_token++].type = TK_NEG;
            }
            else tokens[nr_token++].type = '-';
            break;
          }
          case '*': {
            if (nr_token == 0 || (nr_token > 0 && ((tokens[nr_token - 1].type != ')') &&
                (tokens[nr_token - 1].type != TK_NUM)))) {
              tokens[nr_token++].type = TK_PTR;
            }
            else tokens[nr_token++].type = '*';
            break;
          }
          // case TK_DEC: tokens[nr_token].type = TK_DEC; strncpy(tokens[nr_token++].str, substr_start, substr_len); break;
          case TK_NUM: tokens[nr_token].type = TK_NUM; strcpy(tokens[nr_token++].str, match); break;
          case TK_REG: tokens[nr_token].type = TK_REG; strcpy(tokens[nr_token++].str, match); break;
          default: tokens[nr_token++].type = rules[i].token_type;
        }
        free(match);
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

static inline bool check_parentheses(int p, int q) {
  if (tokens[p].type != '(')  return false;
  for (int i = p; i < q; i++) {
    if (tokens[i].type == ')')  return false;
  }
  return tokens[q].type == ')';
}

bool eval() {
  if (op_stack[op_ptr - 1].type == TK_NEG) {
    num_stack[num_ptr - 1] = -num_stack[num_ptr - 1];
    op_ptr--;
  }
  else if (op_stack[op_ptr - 1].type == TK_PTR) {
    num_stack[num_ptr - 1] = paddr_read(num_stack[num_ptr - 1], MUXDEF(CONFIG_ISA64, 8, 4));
    op_ptr--;
  }
  else {
    word_t b = num_stack[--num_ptr];
    word_t a = num_stack[--num_ptr];
    switch (op_stack[--op_ptr].type) {
      case '+': num_stack[num_ptr++] = a + b; break;
      case '-': num_stack[num_ptr++] = a - b; break;
      case '*': num_stack[num_ptr++] = a * b; break;
      case '/': {
        // Assert(b != 0, "Error: %ld is divided by 0.", a);
        if (b == 0) {
          printf("Error: %ld is divided by 0.\n", a);
          return false;
        }
        num_stack[num_ptr++] = a / b; break;
      }
      case '%': num_stack[num_ptr++] = a % b; break;
      case TK_LOR:  num_stack[num_ptr++] = a || b; break;
      case TK_LAND: num_stack[num_ptr++] = a && b; break;
      case TK_BOR:  num_stack[num_ptr++] = a | b; break;
      case TK_XOR:  num_stack[num_ptr++] = a ^ b; break;
      case TK_BAND: num_stack[num_ptr++] = a & b; break;
      case TK_EQ:   num_stack[num_ptr++] = a == b; break;
      case TK_NEQ:  num_stack[num_ptr++] = a != b; break;
    }
  }
  return true;
}

inline int pr_lut(int c) {
  switch (c) {
    case TK_LOR:  return 4;
    case TK_LAND: return 5;
    case TK_BOR:  return 6;
    case TK_XOR:  return 7;
    case TK_BAND: return 8;
    case TK_EQ:   return 9;
    case TK_NEQ:  return 9;
    case '+':     return 12;
    case '-':     return 12;
    case '*':     return 13;
    case '/':     return 13;
    case '%':     return 13;
    case TK_NEG:  return 15;
    case TK_REG:  return 15;
    case TK_PTR:  return 15;
    // case '(': return 16;
  }
  return 0;
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    goto error;
  }
  if (nr_token == 0) {
    printf("No expression input.\n");
    goto error;
  }

  // Log("Total token number: %d", nr_token);
  // clear the pointer
  num_ptr = 0;
  op_ptr = 0;
  int bracket_l = 0, bracket_r = 0;
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == '(')  bracket_l++;
    if (tokens[i].type == ')')  bracket_r++;
  }
  if (bracket_r - bracket_l) {
    fprintf(stderr, "Brackets not match, with %d left brackets, %d right brackets\n", bracket_l, bracket_r);
    goto error;
  }

  // Calculate
  for (int i = 0; i < nr_token; i++) {
    if (tokens[i].type == TK_NUM) {
      num_stack[num_ptr++] = strtoul(tokens[i].str, NULL, 0);
    }
    else if (tokens[i].type == TK_REG) {
      // read reg
      bool valid = true;
      word_t regv = isa_reg_str2val(tokens[i].str + 1, &valid);
      if (!valid) {
        printf("Invalid reg name: \"%s\".\n", tokens[i].str + 1);
        goto error;
      }
      num_stack[num_ptr++] = regv;
    }
    else if (tokens[i].type == '(') {
      op_stack[op_ptr++].type = '(';
    }
    else if (tokens[i].type == ')') {
      while (op_stack[op_ptr - 1].type != '(') {
        if (!eval()) goto error;
      }
      op_ptr--;
    }
    else {
        while (op_ptr > 0 && pr_lut(op_stack[op_ptr - 1].type) >= pr_lut(tokens[i].type)) {
          if (!eval()) goto error;
        }
        op_stack[op_ptr++].type = tokens[i].type;
    }
  }
  while (op_ptr > 0) {
    if (!eval()) goto error;
  }

  if (num_ptr != 1){
    printf("Invalid input expression.\n");
    goto error;
  }
  return num_stack[num_ptr - 1];

error:
  *success = false;
  return 0;
}
