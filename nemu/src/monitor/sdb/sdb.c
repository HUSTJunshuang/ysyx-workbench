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
#include <cpu/cpu.h>
#include <memory/paddr.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

/* Extract the args to argv likes the main func, return the arg count */
/* remember to free the argv */
int extract_args(char *args, char ***argv) {
  int argc = 0;
  char *arg = strtok(args, " ");
  printf("args = %s\n", args);
  // char *buf = strdup(args);
  // count arg number
  while (arg != NULL) {
    *argv = realloc(*argv, sizeof(char*) * (argc + 1));
    (*argv)[argc++] = strdup(arg);
    arg = strtok(NULL, " ");
  }
  // extract args
  // *argv = (char **)malloc(sizeof(char *) * argc);
  // if (*argv == NULL) printf("malloc failed\n");
  // for (int i = 0; i < argc; i++) printf("Address of argv[%d]: %p\n", i, &argv[i]);
  // char tmp[512];
  // for (int i = 0; i < argc; i ++) {
  //   sscanf(buf, "%s", tmp);
  //   (*argv)[i] = strdup(tmp);
  //   printf("argv[%d] dumped successfully\n", i);
  // }
  // free(buf);

  return argc;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
  return -1;
}

static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args);
static int cmd_help(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "Single-step execution,\n\tUsage: 'si [N]', N(int) refers to execution times, with a default value 1.", cmd_si },
  { "info", "Display information about regs('info r') or wathcpoints('info w')", cmd_info },
  { "x", "Display memory content,\n\tUasge: 'x N ADDR', N(int) refers to scan length, ADDR refers to the start address, which can be a expression.", cmd_x },
  { "p", "Calculate expressions.", cmd_p },
  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  char **argv;
  int argc = extract_args(args, &argv);
  printf("There are total %d args\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
    free(argv[i]);
  }
  free(argv);

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int cmd_si(char *args) {
  char *arg = strtok(NULL, " ");
  if (arg == NULL) {
    cpu_exec(1);
  }
  else {
    // TODO si x
    int step = atoi(arg);
    cpu_exec(step);
  }
  return 0;
}

static int cmd_info(char *args) {
  char *arg = strtok(NULL, " ");
  if (arg == NULL) {
    goto error;
  }
  if (strcmp(arg, "r") == 0) {
    isa_reg_display();
  }
  else if (strcmp(arg, "w") == 0) {
    // TODO print watchpoint
    printf("TBD\n");
  }
  else {
    goto error;
  }
  return 0;

error:
  printf("Usage: 'info r'(show regs value) or 'info w'(show watchpoints)\n");
  return 0;
}

static int cmd_x(char *args) {
  paddr_t addr;
  int len;
  int ret;
  char extra[512] = "";
  // process len
  char *arg = strtok(NULL, " ");
  if (arg == NULL)  goto error;
  ret = sscanf(arg, "%d%s", &len, extra);
  printf("ret = %d\n", ret);
  printf("extra = %s\n", extra);
  if (ret != 1)  goto error;
  // process address
  arg = strtok(NULL, " ");
  if (arg == NULL)  goto error;
  ret = sscanf(arg, "0x%x %s", &addr, extra);
  printf("ret = %d\n", ret);
  printf("extra = %s\n", extra);
  if (ret != 1)  goto error;
  // four word in a line
  for (int i = 0; i < len; i += 4) {
    printf("0x%x <tag>:", addr + i * 4);
    for (int j = 0; j < 4; j++) {
      int offset = i + j;
      if (offset >= len) break;
      uint32_t m = paddr_read(addr + offset * 4, 4);
      printf("\t0x%08x", m);
    }
    printf("\n");
  }
  return 0;

error:
  printf("Usage: 'x N ADDR', N(int) refers to scan length, ADDR refers to the start address, which can be a expression.\n");
  return 0;
}

static int cmd_p(char *args) {
  bool success = true;
  word_t result = expr(args, &success);
  if (success) printf("%ld\n", result);
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    // BUG can't handle extra parameter like GDB dose
    // for example, won't throw error when get 'help c d e f g'
    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
