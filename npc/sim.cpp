#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated_fst_c.h"

VerilatedContext* cp;
Vtop* top;
VerilatedFstC *tfp;

const int MAX_INST = 10;
int inst_mem[MAX_INST];
int inst_cnt = 0;

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

    // fill instruction memory
    for (int i = 0; i < MAX_INST; i++) {
        inst_mem[i] = 0x00208093;
    }

    reset(10);
    while (inst_cnt < MAX_INST) {
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