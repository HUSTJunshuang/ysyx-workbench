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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"#include <stdint.h>\n"
"int main() { "
"  uint64_t result = (uint64_t)%s; "
"  printf(\"%%lu\", result); "
"  return 0; "
"}";

static int DEPTH = 0;

// parameters
#define OP_SIZE 4
#define MAX_SPACE_LEN 1
const int MAX_DEPTH = 32;
const char *OP_LIST[OP_SIZE] = {"+", "-", "*", "/"};
const uint64_t MAX_UINT = 0x000000000000ffff;

// function declarations
static inline void gen_reset();
static inline uint64_t choose(uint64_t n);
static inline void gen(const char *s);
static inline void gen_num();
static inline void gen_rand_op();
static inline void gen_space();

static void gen_rand_expr() {
  if (++DEPTH > MAX_DEPTH) {
    // if reached the threshold, just generate a number
    gen_space(); gen_num(); gen_space();
    return ;
  }
  switch (choose(3)) {
    case 0: gen_space(); gen_num(); gen_space(); break;
    case 1: gen("("); gen_rand_expr(); gen(")"); break;
    default: gen_rand_expr(); gen_space(); gen_rand_op(); gen_space(); gen_rand_expr(); break;
  }
  return ;
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    gen_reset();
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    // add a gcc option "-Werror" to filter the div-by-zero warning
    // To disable error info generated by gcc, redirect it to /dev/null
    int ret = system("gcc /tmp/.code.c -Werror=div-by-zero -o /tmp/.expr >/dev/null 2>&1");
    // int ret = system("gcc /tmp/.code.c -Werror=div-by-zero -o /tmp/.expr");
    // TODO reason of why the return value of system func turns to 0
    // int ret = system("gcc /tmp/.code.c -Werror=div-by-zero -o /tmp/.expr &> /dev/null");
    // printf("ret = %d\n", ret);
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    uint64_t result;
    ret = fscanf(fp, "%lu", &result);
    pclose(fp);

    printf("%lu %s\n", result, buf);
    if (i % 50 == 0) fprintf(stderr, "Running, finished %d/%d\n", i, loop);
  }
  return 0;
}

static inline void gen_reset() {
  buf[0] = '\0';
  DEPTH = 0;
  return ;
}

static inline uint64_t choose(uint64_t n) {
  return rand() % n;
}

static inline void gen(const char *s) {
  strcat(buf, s);
  return ;
}

static inline void gen_num() {
  uint64_t num = choose(MAX_UINT);
  char tmp[32];
  sprintf(tmp, "%luUL", num);
  strcat(buf, tmp);
  return ;
}

static inline void gen_rand_op() {
  gen(OP_LIST[choose(OP_SIZE)]);
  return ;
}

static inline void gen_space() {
  int cnt = choose(MAX_SPACE_LEN + 1);
  char tmp[MAX_SPACE_LEN + 1];
  sprintf(tmp, "%*s", cnt, "");
  strcat(buf, tmp);
  return ;
}
