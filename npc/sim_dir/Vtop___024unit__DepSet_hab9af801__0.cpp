// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vtop__Syms.h"
#include "Vtop___024unit.h"

extern "C" void set_nemu_state(int state);

VL_INLINE_OPT void Vtop___024unit____Vdpiimwrap_set_nemu_state_TOP____024unit(IData/*31:0*/ state) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_set_nemu_state_TOP____024unit\n"); );
    // Body
    int state__Vcvt;
    for (size_t state__Vidx = 0; state__Vidx < 1; ++state__Vidx) state__Vcvt = state;
    set_nemu_state(state__Vcvt);
}
