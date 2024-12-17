#include <common.h>

#ifndef CONFIG_TARGET_AM

// ftrace, invocation control block
typedef struct {
  int call_depth;
} ICB;

static ICB icb;

void init_icb() {
    icb.call_depth = 0;
}

#if (__GUEST_ISA__ == riscv32 || __GUEST_ISA__ == riscv64)
void check_invoke(uint32_t inst, vaddr_t pc, vaddr_t dnpc, int ret) {
    int rd = BITS(inst, 11, 7);
    int rs1 = BITS(inst, 19, 15);
    if (rd == 1 || rd == 5) {
        printf(FMT_WORD ": %*scall [???@" FMT_WORD "]\n", pc, icb.call_depth * 2, "", dnpc);
        ++icb.call_depth;
    }
    if (ret == 1 && rd == 0 && rs1 == 1) {
        --icb.call_depth;
        printf(FMT_WORD ": %*sret  [???]\n", pc, icb.call_depth * 2, "");
    }
}
#endif

#endif
