#include <memory/host.h>
#include <memory/paddr.h>
#include "sdb.h"

#ifdef CONFIG_ITRACE

// for disassemble
void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
// print instruction
inline void display_inst(uint8_t * inst, int ilen) {
    for (int i = ilen - 1; i >= 0; --i) {
        printf(" %02x", inst[i]);
    }
}

#define iRB_CAP 8
#define TAIL_LEN 4

static iRB iringbuf = {iRB_CAP};
char str_buf[128];
const int ilen = 4;

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
    uint8_t *inst;
    // check started or not
    if (iringbuf.size == 0) return ;
    printf(ANSI_FMT("Encountered an error while executing the following snippets:", ANSI_FG_MAGENTA) "\n");
    if (iringbuf.size == iringbuf.capacity) printf("%6s......\n", "");
    // instructions executed
    for (int i = 0; i < iringbuf.size; ++i) {
        inst = (uint8_t *)&iringbuf.inst_buf[rptr];
        printf("%6s" FMT_WORD ":", "", iringbuf.pc_buf[rptr]);
        display_inst(inst, ilen);
        disassemble(str_buf, sizeof(str_buf), iringbuf.pc_buf[rptr], inst, ilen);
        printf("\t%s\n", str_buf);
        rptr = (rptr + 1) % iringbuf.capacity;
    }
    // error instruction
    MUXDEF(CONFIG_ISA_x86, uint64_t, uint32_t) inst_val = host_read(guest_to_host(pc), ilen);
    inst = (uint8_t *)&inst_val;
    printf("  --> " FMT_WORD ":", pc);
    display_inst(inst, ilen);
    disassemble(str_buf, sizeof(str_buf), pc, inst, ilen);
    printf("\t%s\n", str_buf);
    // instructions behind
    for (int i = 0; i < TAIL_LEN; ++i) {
        pc += ilen;
        inst_val = host_read(guest_to_host(pc), ilen);
        inst = (uint8_t *)&inst_val;
        printf("%6s" FMT_WORD ":", "", pc);
        display_inst(inst, ilen);
        disassemble(str_buf, sizeof(str_buf), pc, inst, ilen);
        printf("\t%s\n", str_buf);
    }
    printf("%6s......\n", "");
}

void destory_iRB() {
    free(iringbuf.pc_buf);
    free(iringbuf.inst_buf);
    return ;
}

#endif
