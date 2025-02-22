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

#ifdef CONFIG_ETRACE
static const char *intr_desc[256] = {
  [0]   = "Reserved",
};
static const char *excp_desc[256] = {
  [8]   = "Environment call from U-mode or VU-mode",
  [9]   = "Environment call from HS-mode",
  [10]  = "Environment call from VS-mode",
  [11]  = "Environment call from S-mode",
};
#endif

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  cpu.csr[mepc] = epc;
  cpu.csr[mcause] = NO;
  #ifdef CONFIG_ETRACE
  word_t interrupt = NO >> MUXDEF(CONFIG_RV64, 63, 31);
  word_t index = (NO << 1) >> 1;
  Log("%s(Code" FMT_DEC ") raised at pc = " FMT_WORD " : %s", interrupt ? "Interrupt" : "Exception", NO,
      epc, interrupt ? intr_desc[index] : excp_desc[index]);
  #endif

  return cpu.csr[mtvec];
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
