// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v0;
    __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v0 = 0;
    CData/*4:0*/ __Vdlyvdim0__top__DOT__inst_RegFile__DOT__regfile__v31;
    __Vdlyvdim0__top__DOT__inst_RegFile__DOT__regfile__v31 = 0;
    QData/*63:0*/ __Vdlyvval__top__DOT__inst_RegFile__DOT__regfile__v31;
    __Vdlyvval__top__DOT__inst_RegFile__DOT__regfile__v31 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v31;
    __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v31 = 0;
    // Body
    __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v0 = 0U;
    __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v31 = 0U;
    if (vlSelf->rst) {
        vlSelf->top__DOT__inst_RegFile__DOT__i = 0x20U;
        vlSelf->top__DOT__PC = 0x80000000ULL;
        __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v0 = 1U;
    } else {
        vlSelf->top__DOT__PC = (1ULL + vlSelf->top__DOT__PC);
        if (((IData)(vlSelf->top__DOT__dst_valid) & 
             (0U != (0x1fU & (vlSelf->inst >> 7U))))) {
            __Vdlyvval__top__DOT__inst_RegFile__DOT__regfile__v31 
                = vlSelf->top__DOT__dst;
            __Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v31 = 1U;
            __Vdlyvdim0__top__DOT__inst_RegFile__DOT__regfile__v31 
                = (0x1fU & (vlSelf->inst >> 7U));
        }
    }
    if (__Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v0) {
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[1U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[2U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[3U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[4U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[5U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[6U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[7U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[8U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[9U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0xaU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0xbU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0xcU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0xdU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0xeU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0xfU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x10U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x11U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x12U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x13U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x14U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x15U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x16U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x17U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x18U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x19U] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x1aU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x1bU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x1cU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x1dU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x1eU] = 0ULL;
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[0x1fU] = 0ULL;
    }
    if (__Vdlyvset__top__DOT__inst_RegFile__DOT__regfile__v31) {
        vlSelf->top__DOT__inst_RegFile__DOT__regfile[__Vdlyvdim0__top__DOT__inst_RegFile__DOT__regfile__v31] 
            = __Vdlyvval__top__DOT__inst_RegFile__DOT__regfile__v31;
    }
    vlSelf->pc = vlSelf->top__DOT__PC;
}

void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
    }
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vtop___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/junshuang/Project/ysyx/ysyx-workbench/npc/vsrc/top.v", 5, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vtop___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/junshuang/Project/ysyx/ysyx-workbench/npc/vsrc/top.v", 5, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/junshuang/Project/ysyx/ysyx-workbench/npc/vsrc/top.v", 5, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
