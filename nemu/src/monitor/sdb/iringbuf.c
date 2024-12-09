#include <memory/paddr.h>
#include "sdb.h"

// for disassemble
void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

#define iRB_CAP 8
#define TAIL_LEN 4

static iRB iringbuf = {iRB_CAP};
char str_buf[128];

void init_iRB() {
    iringbuf.size = 0;
    iringbuf.pc_buf = (vaddr_t *)malloc(iRB_CAP * sizeof(vaddr_t));
    iringbuf.inst_buf = (MUXDEF(CONFIG_ISA_x86, uint64_t, uint32_t) *)malloc(iRB_CAP * sizeof(MUXDEF(CONFIG_ISA_x86, uint64_t, uint32_t)));
    iringbuf.wptr = 0;
    Assert(iringbuf.pc_buf != NULL, "Init pc_buf failed!");
    Assert(iringbuf.inst_buf != NULL, "Init inst_buf failed!");
    return ;
}

void push_iRB(vaddr_t pc, MUXDEF(CONFIG_ISA_x86, uint64_t, uint32_t) inst) {
    iringbuf.pc_buf[iringbuf.wptr] = pc;
    iringbuf.inst_buf[iringbuf.wptr] = inst;
    if (iringbuf.size < iringbuf.capacity) {
        ++iringbuf.size;
    }
    iringbuf.wptr = (iringbuf.wptr + 1) % iringbuf.capacity;
    return ;
}

void print_iRB(vaddr_t pc) {
    int rptr = (iringbuf.wptr + iringbuf.capacity - iringbuf.size) % iringbuf.capacity;
    printf("iringbuf.size = %d, wptr = %d, rptr = %d\n", iringbuf.size, iringbuf.wptr, rptr);
    // instructions executed
    for (int i = 0; i < iringbuf.size; ++i) {
        disassemble(str_buf, sizeof(str_buf), iringbuf.pc_buf[rptr], (uint8_t *)(iringbuf.inst_buf + rptr), 4);
        printf("%6s" FMT_WORD ": %s\n", "", iringbuf.pc_buf[rptr], str_buf);
        rptr = (rptr + 1) % iringbuf.capacity;
    }
    // error instruction
    MUXDEF(CONFIG_ISA_x86, uint64_t, uint32_t) inst = paddr_read(pc, 4);
    disassemble(str_buf, sizeof(str_buf), pc, (uint8_t *)&inst, 4);
    printf("  --> " FMT_WORD ": %s\n", pc, str_buf);
    // instructions behind
    for (int i = 0; i < TAIL_LEN; ++i) {
        pc += 4;
        inst = paddr_read(pc, 4);
        disassemble(str_buf, sizeof(str_buf), pc, (uint8_t *)&inst, 4);
        printf("%6s" FMT_WORD ": %s\n", "", pc, str_buf);
    }
}

void destory_iRB() {
    free(iringbuf.pc_buf);
    free(iringbuf.inst_buf);
    return ;
}
