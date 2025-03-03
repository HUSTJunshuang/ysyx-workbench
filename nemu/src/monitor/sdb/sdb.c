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
#include <utils.h>
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
/* The argv should be NULL before call, and remember to free the argv */
int extract_args(char *args, char ***argv) {
  int argc = 0;
  char *arg = strtok(args, " ");
  while (arg != NULL) {
    *argv = realloc(*argv, sizeof(char*) * (argc + 1));
    (*argv)[argc++] = strdup(arg);
    arg = strtok(NULL, " ");
  }
  return argc;
}
void release_argv(int argc, char **argv) {
  for (int i = 0; i < argc; i++) {
    free(argv[i]);
  }
  free(argv);
}

static int cmd_c(char *args);
static int cmd_q(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args);
static int cmd_help(char *args);
static int cmd_w(char *args);
static int cmd_d(char *args);

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
  { "x", "Display memory content,\n\tUasge: 'x [N] ADDR', N(int) refers to scan length with a default value 1, ADDR refers to the start address, which can be a expression.", cmd_x },
  { "p", "Calculate expressions.", cmd_p },
  { "w", "Add watchpoint.", cmd_w},
  { "d", "Delete watchpoint by the id,\n\tUsage: 'd ID0 ... IDx', ID(int) refers to the watchpoint id to be deleted.", cmd_d}

};

#define NR_CMD ARRLEN(cmd_table)

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
  IFDEF(CONFIG_WATCHPOINT, init_wp_pool());

  /* Initialize the instruction ringbuffer. */
  IFDEF(CONFIG_ITRACE, init_iRB());
}



/* ---------- Function Implementations ---------- */
static int cmd_c(char *args) {
  if (nemu_state.state != NEMU_END && nemu_state.state != NEMU_ABORT) {
    if (!is_batch_mode) printf("Continuing.\n");
  }
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  nemu_state.state = NEMU_QUIT;
  return -1;
}

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

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
  char **argv = NULL;
  int argc = extract_args(args, &argv);

  if (argc == 0) {
    cpu_exec(1);
  }
  else if (argc == 1) {
    char *end_ptr = NULL;
    uint64_t step = strtoul(argv[0], &end_ptr, 0);
    if (argv[0] + strlen(argv[0]) != end_ptr) {
      printf("Step size (%s) not valid, please input a integer.\n", argv[0]);
      goto error;
    }
    else {
      cpu_exec(step);
    }
  }
  else {
    printf("Too many arguments.\n");
    goto error;
  }
  release_argv(argc, argv);
  return 0;

error:
  release_argv(argc, argv);
  printf("Usage: 'si [N]', N(int) refers to execution times, with a default value 1.\n");
  return 0;
}

static int cmd_info(char *args) {
  char **argv = NULL;
  int argc = extract_args(args, &argv);
  if (argc != 1) {
    goto error;
  }

  if (strcmp(argv[0], "r") == 0) {
    isa_reg_display();
  }
  else if (strcmp(argv[0], "w") == 0) {
#ifndef CONFIG_WATCHPOINT
    printf("Watchpoint not enabled, please change the configuration by execute 'make menuconfig'\n");
#else
    print_wp();
#endif
  }
  else {
    goto error;
  }
  release_argv(argc, argv);
  return 0;

error:
  release_argv(argc, argv);
  printf("Usage: 'info r'(show regs value) or 'info w'(show watchpoints).\n");
  return 0;
}

static int cmd_x(char *args) {
  char **argv = NULL;
  int argc = extract_args(args, &argv);
  if (argc == 0) {
    goto error;
  }

  paddr_t addr = 0;
  int N = 1;
  char *end_ptr = NULL;
  if (argc == 1) {
    // scan one word pointed by ADDR
    addr = strtoul(argv[0], &end_ptr, 0);
    if (argv[0] + strlen(argv[0]) != end_ptr) {
      printf("Address (%s) not valid, please input a integer.\n", argv[0]);
      goto error;
    }
  }
  else if (argc == 2) {
    // scan N words pointed by ADDR
    N = strtoul(argv[0], &end_ptr, 0);
    if (argv[0] + strlen(argv[0]) != end_ptr) {
      printf("N (%s) not valid, please input a integer.\n", argv[0]);
      goto error;
    }
    end_ptr = NULL;
    addr = strtoul(argv[1], &end_ptr, 0);
    if (argv[1] + strlen(argv[1]) != end_ptr) {
      printf("Address (%s) not valid, please input a integer.\n", argv[1]);
      goto error;
    }
  }
  else {
    printf("Too many arguments.\n");
    goto error;
  }
  // four words in a line
  for (int i = 0; i < N; i += 4) {
    printf("0x%x <tag>:", addr + i * 4);
    for (int j = 0; j < 4; j++) {
      int offset = i + j;
      if (offset >= N) break;
      uint32_t mem = paddr_read(addr + offset * 4, 4);
      printf("\t0x%08x", mem);
    }
    printf("\n");
  }
  release_argv(argc, argv);
  return 0;

error:
  release_argv(argc, argv);
  printf("Usage: 'x [N] ADDR', N(int) refers to scan length with a default value 1, ADDR refers to the start address, which can be a expression.\n");
  return 0;
}

static int cmd_p(char *args) {
  bool success = true;
  word_t result = expr(args, &success);
  if (success) printf("%ld(%lu)\n", result, result);
  return 0;
}

static int cmd_w(char *args) {
#ifndef CONFIG_WATCHPOINT
  printf("Watchpoint not enabled, please change the configuration by execute 'make menuconfig'\n");
#else
  bool success = true;
  // TODO filter the const value
  word_t val = expr(args, &success);
  if (!success){
    printf(ANSI_FMT("Error: ", ANSI_FG_RED) "Expression evaluation faild.\n");
    goto error;
  }
  WP *wp = new_wp();
  if (wp == NULL) goto error;
  wp->expression = strdup(args);
  wp->old_val = val;
  printf("Watchpoint %d: %s\n", wp->NO, args);
error:
#endif
  return 0;
}

static int cmd_d(char *args) {
#ifndef CONFIG_WATCHPOINT
  printf("Watchpoint not enabled, please change the configuration by execute 'make menuconfig'\n");
#else
  char **argv = NULL;
  int argc = extract_args(args, &argv);
  // TODO support only one ID now
  if (argc != 1) {
    printf("Usage: 'd ID0 ... IDx', ID(int) refers to the watchpoint id to be deleted.\n");
    goto error;
  }
  char *end_ptr = NULL;
  int del_id = strtoul(argv[0], &end_ptr, 10);
  if (argv[0] + strlen(argv[0]) != end_ptr) {
    printf("ID (%s) not valid.\n", argv[0]);
    goto error;
  }
  free_wp(del_id);
error:
  release_argv(argc, argv);
#endif
  return 0;
}
