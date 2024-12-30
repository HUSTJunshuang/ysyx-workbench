#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated_fst_c.h"
// for DPI-C
#include "svdpi.h"
#include "Vtop__Dpi.h"

VerilatedContext* cp;
Vtop* top;
VerilatedFstC *tfp;

// cpu status
// CHECK need how many status
enum { NEMU_RUNNING, NEMU_STOP, NEMU_END, NEMU_ABORT, NEMU_QUIT };
int nemu_state = 0;

const int MAX_INST = 100;
// TODO use dpi-c function to r/w mem in verilog
int inst_mem[MAX_INST];
int inst_cnt = 0;

static long load_img() {
}

// DPI-C functions
void set_nemu_state(int state) {
    nemu_state = state;
    return ;
}

static void single_cycle() {
    cp->timeInc(5);
    top->clk = 0; top->eval(); tfp->dump(cp->time());
    cp->timeInc(5);
    top->clk = 1; top->eval(); tfp->dump(cp->time());
}

static void reset(int cycles) {
    top->rst = 1;
    for (int i = 0; i < cycles; i++) {
        single_cycle();
    }
    top->rst = 0;
}

int main() {
    // define context pointer and top module pointer
	cp = new VerilatedContext;
	top = new Vtop{cp};
	// enable trace and define VerilatedVcdC object
	Verilated::traceEverOn(true);
	tfp = new VerilatedFstC;
	// set trace level and output file
	top->trace(tfp, 3);
	Verilated::mkdir("waves");
	tfp->open("waves/sim.vcd");

    // TODO define a function to read img file from shell
    // reference: /home/junshuang/Project/ysyx/ysyx-workbench/nemu/src/monitor/monitor.c:49 load_img()
    // fill instruction memory
    for (int i = 0; i < 10; i++) {
        assert(i < MAX_INST);
        inst_mem[i] = 0x00208093;
    }
    inst_mem[10] = 0x00100073;

    reset(10);
    while (nemu_state == NEMU_RUNNING) {
        top->inst = inst_mem[inst_cnt++];
        single_cycle();
    }
    top->final();
    // close dump file
    tfp->close();
    delete top;
    delete cp;

    return 0;
}