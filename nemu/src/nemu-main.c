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

#include <common.h>

#include "monitor/sdb/sdb.h"

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

// test func
void func_check();
void p_test();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
  #ifdef CONFIG_POST
  /* Self check */
  func_check();
  #endif
#endif

  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}

#ifndef CONFIG_TARGET_AM
void func_check() {
  Log("Starting to check functions of nemu.");

  p_test();

  Log("Function check finished.");
}

void p_test() {
  char *NEMU_HOME = getenv("NEMU_HOME");
  if (NEMU_HOME == NULL) {
    printf("env var 'NEMU_HOME' is not set.\n");
    return ;
  }
  FILE *fp = fopen(strcat(NEMU_HOME, "/tools/gen-expr/expr_test.txt"), "r");
  if (fp == NULL) {
    printf("Error to open file \"%s\".\n", NEMU_HOME);
    return ;
  }

  int err_cnt = 0;
  char buf[4096];
  word_t answer, result;
  while (fgets(buf, sizeof(buf), fp) != NULL) {
    bool success = true;
    char *ans = strtok(buf, " ");
    char *e = strtok(NULL, "\n");
    char *end_ptr = NULL;
    char *raw_expr = strdup(e);
    answer = strtoul(ans, &end_ptr, 0);
    result = expr(e, &success);
    if (success) {
      if (result != answer) {
        printf("Expr %s get %lu, instead of %lu\n", raw_expr, result, answer);
        if (err_cnt++ > 10) return ;
      }
    }
    else {
      printf("Failed to calc %s\n", raw_expr);
      if (err_cnt++ > 10) return ;
    }
    free(raw_expr);
  }
  fclose(fp);

  if (err_cnt == 0) Log("Expression evaluation test Passed!");
  else Log("Expression evaluation test Passed!");
  return ;
}
#endif
