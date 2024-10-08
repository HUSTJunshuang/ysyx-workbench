// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "Vtop__Syms.h"
#include "Vtop___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers__ico\n"); );
    // Body
    vlSelf->__VicoTriggered.at(0U) = (0U == vlSelf->__VicoIterCount);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

void Vtop___024unit____Vdpiimwrap_set_nemu_state_TOP____024unit(IData/*31:0*/ state);

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->top__DOT__opcode = (0x7fU & vlSelf->inst);
    vlSelf->top__DOT__imm = ((0x40U & (IData)(vlSelf->top__DOT__opcode))
                              ? ((0x20U & (IData)(vlSelf->top__DOT__opcode))
                                  ? ((0x10U & (IData)(vlSelf->top__DOT__opcode))
                                      ? 0ULL : ((8U 
                                                 & (IData)(vlSelf->top__DOT__opcode))
                                                 ? 
                                                ((4U 
                                                  & (IData)(vlSelf->top__DOT__opcode))
                                                  ? 
                                                 ((2U 
                                                   & (IData)(vlSelf->top__DOT__opcode))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(vlSelf->top__DOT__opcode))
                                                    ? 
                                                   (((- (QData)((IData)(
                                                                        (vlSelf->inst 
                                                                         >> 0x1fU)))) 
                                                     << 0x14U) 
                                                    | (QData)((IData)(
                                                                      ((0xff000U 
                                                                        & vlSelf->inst) 
                                                                       | ((0x800U 
                                                                           & (vlSelf->inst 
                                                                              >> 9U)) 
                                                                          | (0x7feU 
                                                                             & (vlSelf->inst 
                                                                                >> 0x14U)))))))
                                                    : 0ULL)
                                                   : 0ULL)
                                                  : 0ULL)
                                                 : 
                                                ((4U 
                                                  & (IData)(vlSelf->top__DOT__opcode))
                                                  ? 
                                                 ((2U 
                                                   & (IData)(vlSelf->top__DOT__opcode))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(vlSelf->top__DOT__opcode))
                                                    ? 
                                                   (((- (QData)((IData)(
                                                                        (vlSelf->inst 
                                                                         >> 0x1fU)))) 
                                                     << 0xcU) 
                                                    | (QData)((IData)(
                                                                      (vlSelf->inst 
                                                                       >> 0x14U))))
                                                    : 0ULL)
                                                   : 0ULL)
                                                  : 
                                                 ((2U 
                                                   & (IData)(vlSelf->top__DOT__opcode))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(vlSelf->top__DOT__opcode))
                                                    ? 
                                                   (((- (QData)((IData)(
                                                                        (vlSelf->inst 
                                                                         >> 0x1fU)))) 
                                                     << 0xcU) 
                                                    | (QData)((IData)(
                                                                      ((0x800U 
                                                                        & (vlSelf->inst 
                                                                           << 4U)) 
                                                                       | ((0x7e0U 
                                                                           & (vlSelf->inst 
                                                                              >> 0x14U)) 
                                                                          | (0x1eU 
                                                                             & (vlSelf->inst 
                                                                                >> 7U)))))))
                                                    : 0ULL)
                                                   : 0ULL))))
                                  : 0ULL) : ((0x20U 
                                              & (IData)(vlSelf->top__DOT__opcode))
                                              ? ((0x10U 
                                                  & (IData)(vlSelf->top__DOT__opcode))
                                                  ? 
                                                 ((8U 
                                                   & (IData)(vlSelf->top__DOT__opcode))
                                                   ? 0ULL
                                                   : 
                                                  ((4U 
                                                    & (IData)(vlSelf->top__DOT__opcode))
                                                    ? 
                                                   ((2U 
                                                     & (IData)(vlSelf->top__DOT__opcode))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelf->top__DOT__opcode))
                                                      ? 
                                                     (((- (QData)((IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x1fU)))) 
                                                       << 0x1fU) 
                                                      | (QData)((IData)(
                                                                        (0x7ffff000U 
                                                                         & vlSelf->inst))))
                                                      : 0ULL)
                                                     : 0ULL)
                                                    : 0ULL))
                                                  : 
                                                 ((8U 
                                                   & (IData)(vlSelf->top__DOT__opcode))
                                                   ? 0ULL
                                                   : 
                                                  ((4U 
                                                    & (IData)(vlSelf->top__DOT__opcode))
                                                    ? 0ULL
                                                    : 
                                                   ((2U 
                                                     & (IData)(vlSelf->top__DOT__opcode))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelf->top__DOT__opcode))
                                                      ? 
                                                     (((- (QData)((IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x1fU)))) 
                                                       << 0xcU) 
                                                      | (QData)((IData)(
                                                                        ((0xfe0U 
                                                                          & (vlSelf->inst 
                                                                             >> 0x14U)) 
                                                                         | (0x1fU 
                                                                            & (vlSelf->inst 
                                                                               >> 7U))))))
                                                      : 0ULL)
                                                     : 0ULL))))
                                              : ((0x10U 
                                                  & (IData)(vlSelf->top__DOT__opcode))
                                                  ? 
                                                 ((8U 
                                                   & (IData)(vlSelf->top__DOT__opcode))
                                                   ? 0ULL
                                                   : 
                                                  ((4U 
                                                    & (IData)(vlSelf->top__DOT__opcode))
                                                    ? 
                                                   ((2U 
                                                     & (IData)(vlSelf->top__DOT__opcode))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelf->top__DOT__opcode))
                                                      ? 
                                                     (((- (QData)((IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x1fU)))) 
                                                       << 0x1fU) 
                                                      | (QData)((IData)(
                                                                        (0x7ffff000U 
                                                                         & vlSelf->inst))))
                                                      : 0ULL)
                                                     : 0ULL)
                                                    : 
                                                   ((2U 
                                                     & (IData)(vlSelf->top__DOT__opcode))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelf->top__DOT__opcode))
                                                      ? 
                                                     (((- (QData)((IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x1fU)))) 
                                                       << 0xcU) 
                                                      | (QData)((IData)(
                                                                        (vlSelf->inst 
                                                                         >> 0x14U))))
                                                      : 0ULL)
                                                     : 0ULL)))
                                                  : 
                                                 ((8U 
                                                   & (IData)(vlSelf->top__DOT__opcode))
                                                   ? 0ULL
                                                   : 
                                                  ((4U 
                                                    & (IData)(vlSelf->top__DOT__opcode))
                                                    ? 0ULL
                                                    : 
                                                   ((2U 
                                                     & (IData)(vlSelf->top__DOT__opcode))
                                                     ? 
                                                    ((1U 
                                                      & (IData)(vlSelf->top__DOT__opcode))
                                                      ? 
                                                     (((- (QData)((IData)(
                                                                          (vlSelf->inst 
                                                                           >> 0x1fU)))) 
                                                       << 0xcU) 
                                                      | (QData)((IData)(
                                                                        (vlSelf->inst 
                                                                         >> 0x14U))))
                                                      : 0ULL)
                                                     : 0ULL))))));
    if ((0x13U == (IData)(vlSelf->top__DOT__opcode))) {
        if ((0U == (7U & (vlSelf->inst >> 0xcU)))) {
            vlSelf->top__DOT__dst = (vlSelf->top__DOT__inst_RegFile__DOT__regfile
                                     [(0x1fU & (vlSelf->inst 
                                                >> 0xfU))] 
                                     + vlSelf->top__DOT__imm);
            vlSelf->top__DOT__dst_valid = 1U;
        } else {
            vlSelf->top__DOT__dst = 0ULL;
            vlSelf->top__DOT__dst_valid = 0U;
        }
    } else if ((0x73U == (IData)(vlSelf->top__DOT__opcode))) {
        if ((1U & (~ (vlSelf->inst >> 0xeU)))) {
            if ((1U & (~ (vlSelf->inst >> 0xdU)))) {
                if ((1U & (~ (vlSelf->inst >> 0xcU)))) {
                    if ((1U & (IData)(vlSelf->top__DOT__imm))) {
                        Vtop___024unit____Vdpiimwrap_set_nemu_state_TOP____024unit(2U);
                    }
                }
            }
        }
    } else {
        vlSelf->top__DOT__dst = 0ULL;
        vlSelf->top__DOT__dst_valid = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.at(0U) = ((IData)(vlSelf->clk) 
                                      & (~ (IData)(vlSelf->__Vtrigrprev__TOP__clk)));
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    // Body
    if ((0x13U == (IData)(vlSelf->top__DOT__opcode))) {
        if ((0U == (7U & (vlSelf->inst >> 0xcU)))) {
            vlSelf->top__DOT__dst = (vlSelf->top__DOT__inst_RegFile__DOT__regfile
                                     [(0x1fU & (vlSelf->inst 
                                                >> 0xfU))] 
                                     + vlSelf->top__DOT__imm);
            vlSelf->top__DOT__dst_valid = 1U;
        } else {
            vlSelf->top__DOT__dst = 0ULL;
            vlSelf->top__DOT__dst_valid = 0U;
        }
    } else if ((0x73U == (IData)(vlSelf->top__DOT__opcode))) {
        if ((1U & (~ (vlSelf->inst >> 0xeU)))) {
            if ((1U & (~ (vlSelf->inst >> 0xdU)))) {
                if ((1U & (~ (vlSelf->inst >> 0xcU)))) {
                    if ((1U & (IData)(vlSelf->top__DOT__imm))) {
                        Vtop___024unit____Vdpiimwrap_set_nemu_state_TOP____024unit(2U);
                    }
                }
            }
        }
    } else {
        vlSelf->top__DOT__dst = 0ULL;
        vlSelf->top__DOT__dst_valid = 0U;
    }
}
