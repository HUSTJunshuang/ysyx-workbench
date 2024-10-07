// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgCData(oldp+0,(vlSelf->top__DOT__opcode),7);
        bufp->chgQData(oldp+1,(vlSelf->top__DOT__imm),64);
        bufp->chgBit(oldp+3,(vlSelf->top__DOT__dst_valid));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgQData(oldp+4,(vlSelf->top__DOT__PC),64);
        bufp->chgIData(oldp+6,(vlSelf->top__DOT__inst_RegFile__DOT__i),32);
        bufp->chgQData(oldp+7,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[0]),64);
        bufp->chgQData(oldp+9,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[1]),64);
        bufp->chgQData(oldp+11,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[2]),64);
        bufp->chgQData(oldp+13,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[3]),64);
        bufp->chgQData(oldp+15,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[4]),64);
        bufp->chgQData(oldp+17,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[5]),64);
        bufp->chgQData(oldp+19,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[6]),64);
        bufp->chgQData(oldp+21,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[7]),64);
        bufp->chgQData(oldp+23,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[8]),64);
        bufp->chgQData(oldp+25,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[9]),64);
        bufp->chgQData(oldp+27,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[10]),64);
        bufp->chgQData(oldp+29,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[11]),64);
        bufp->chgQData(oldp+31,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[12]),64);
        bufp->chgQData(oldp+33,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[13]),64);
        bufp->chgQData(oldp+35,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[14]),64);
        bufp->chgQData(oldp+37,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[15]),64);
        bufp->chgQData(oldp+39,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[16]),64);
        bufp->chgQData(oldp+41,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[17]),64);
        bufp->chgQData(oldp+43,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[18]),64);
        bufp->chgQData(oldp+45,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[19]),64);
        bufp->chgQData(oldp+47,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[20]),64);
        bufp->chgQData(oldp+49,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[21]),64);
        bufp->chgQData(oldp+51,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[22]),64);
        bufp->chgQData(oldp+53,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[23]),64);
        bufp->chgQData(oldp+55,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[24]),64);
        bufp->chgQData(oldp+57,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[25]),64);
        bufp->chgQData(oldp+59,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[26]),64);
        bufp->chgQData(oldp+61,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[27]),64);
        bufp->chgQData(oldp+63,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[28]),64);
        bufp->chgQData(oldp+65,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[29]),64);
        bufp->chgQData(oldp+67,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[30]),64);
        bufp->chgQData(oldp+69,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[31]),64);
    }
    bufp->chgBit(oldp+71,(vlSelf->clk));
    bufp->chgBit(oldp+72,(vlSelf->rst));
    bufp->chgIData(oldp+73,(vlSelf->inst),32);
    bufp->chgQData(oldp+74,(vlSelf->pc),64);
    bufp->chgQData(oldp+76,(vlSelf->top__DOT__inst_RegFile__DOT__regfile
                            [(0x1fU & (vlSelf->inst 
                                       >> 0xfU))]),64);
    bufp->chgQData(oldp+78,(vlSelf->top__DOT__inst_RegFile__DOT__regfile
                            [(0x1fU & (vlSelf->inst 
                                       >> 0x14U))]),64);
    bufp->chgCData(oldp+80,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->chgCData(oldp+81,((vlSelf->inst >> 0x19U)),7);
    bufp->chgCData(oldp+82,((0x1fU & (vlSelf->inst 
                                      >> 7U))),5);
    bufp->chgCData(oldp+83,((0x1fU & (vlSelf->inst 
                                      >> 0xfU))),5);
    bufp->chgCData(oldp+84,((0x1fU & (vlSelf->inst 
                                      >> 0x14U))),5);
    bufp->chgQData(oldp+85,(((0x13U == (IData)(vlSelf->top__DOT__opcode))
                              ? ((0U == (7U & (vlSelf->inst 
                                               >> 0xcU)))
                                  ? (vlSelf->top__DOT__inst_RegFile__DOT__regfile
                                     [(0x1fU & (vlSelf->inst 
                                                >> 0xfU))] 
                                     + vlSelf->top__DOT__imm)
                                  : 0ULL) : 0ULL)),64);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
