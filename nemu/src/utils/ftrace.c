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

void check_invoke(vaddr_t pc, vaddr_t dnpc, int rd, int rs1, int ret) {
    if (rd == 1 || rd == 5) {
        printf(FMT_WORD ": %*scall [???@" FMT_WORD "]\n", pc, icb.call_depth * 2, "", dnpc);
        ++icb.call_depth;
    }
    if (ret == 1 && rd == 0 && rs1 == 1) {
        printf(FMT_WORD ": %*sret  [???@" FMT_WORD "]\n", pc, icb.call_depth * 2, "", dnpc);
        --icb.call_depth;
    }
}
#endif
