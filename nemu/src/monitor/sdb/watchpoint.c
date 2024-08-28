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

#include "sdb.h"

#define NR_WP 32



static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *tail = NULL, *free_ = NULL;
static int wp_id = 0;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].front = (i == 0) ? NULL : &wp_pool[i - 1];
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    wp_pool[i].expression = NULL;
    wp_pool[i].old_val = 0;
  }

  head = NULL;
  tail = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp() {
  WP *ret = NULL;
  if (free_ == NULL) {
    printf("No free Watchpoint, please release some of it.\n");
  }
  else {
    ret = free_;
    free_ = free_->next;
    if (free_ != NULL) {
      free_->front = NULL;
    }
    // add to head
    ret->NO = ++wp_id;
    ret->front = NULL;
    ret->next = head;
    if (head != NULL){
      head->front = ret;
    }
    else{
      tail = ret;
    }
    head = ret;
  }
  return ret;
}

void free_wp(int wp_id) {
  WP *wp = head;
  while (wp != NULL) {
    if (wp->NO == wp_id) break;
    wp = wp->next;
  }
  // Assert(wp != NULL, "Not a valid watchpoint, maybe double freed.");
  if (wp == NULL) {
    printf("Invalid id, no watchpoint denoted by %d\n", wp_id);
    goto error;
  }
  // if in the head
  if (wp->front == NULL) {
    head = wp->next;
  }
  else {
    wp->front->next = wp->next;
  }
  // if not in the tail
  if (wp->next != NULL) {
    wp->next->front = wp->front;
  }
  else {
    tail = wp->front;
  }
  // free the expression
  free(wp->expression);
  // add to free_
  wp->front = NULL;
  wp->next = free_;
  free_->front = wp;
  free_ = wp;
error:
  return ;
}

void print_wp() {
  // travel from the tail
  if (tail == NULL) {
    printf("No watchpoints.\n");
    return ;
  }
  WP *wp = tail;
  printf("%-8s%s\n", "ID", "What");
  while (wp != NULL) {
    printf("%-8d%s\n", wp->NO, wp->expression);
    wp = wp->front;
  }
  return ;
}
