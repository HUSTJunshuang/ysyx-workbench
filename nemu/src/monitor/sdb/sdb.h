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

#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>

word_t expr(char *e, bool *success);

typedef struct watchpoint {
  int NO;
  struct watchpoint *front, *next;

  char *expression;
  word_t old_val;
} WP;

WP* new_wp();
void free_wp(int wp_id);
void print_wp();
bool check_wp();

typedef struct {
  const int capacity;
  int size;
  vaddr_t *pc_buf;
  // max instruction length: x86 -> 8B, others -> 4B
  MUXDEF(CONFIG_ISA_x86, uint64_t, uint32_t) *inst_buf;
  int wptr;
} iRB;

void init_iRB();
void push_iRB(vaddr_t pc, MUXDEF(CONFIG_ISA_x86, uint64_t, uint32_t) inst);
void print_iRB(vaddr_t pc);
void destory_iRB();

#endif
