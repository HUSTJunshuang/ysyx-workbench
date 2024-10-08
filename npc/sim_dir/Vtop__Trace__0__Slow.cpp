// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vtop__Syms.h"


VL_ATTR_COLD void Vtop___024root__trace_init_sub__TOP__0(Vtop___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+68,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+69,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+70,"inst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declQuad(c+71,"pc",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->pushNamePrefix("top ");
    tracep->declBus(c+88,"XLEN",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+89,"ILEN",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBit(c+68,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+69,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+70,"inst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declQuad(c+71,"pc",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declQuad(c+1,"PC",-1, FST_VD_IMPLICIT,FST_VT_SV_LOGIC, false,-1, 63,0);
    tracep->declQuad(c+73,"src1",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declQuad(c+75,"src2",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declBus(c+77,"opcode",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+78,"funct3",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 2,0);
    tracep->declBus(c+79,"funct7",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+80,"rd",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+81,"rs1",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+82,"rs2",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declQuad(c+83,"imm",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declQuad(c+85,"dst",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declBit(c+87,"dst_valid",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1);
    tracep->pushNamePrefix("inst_EXU ");
    tracep->declBus(c+88,"XLEN",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBit(c+68,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+69,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+77,"opcode",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+78,"funct3",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 2,0);
    tracep->declBus(c+79,"funct7",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declQuad(c+73,"src1",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declQuad(c+75,"src2",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declQuad(c+83,"imm",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declQuad(c+85,"dst",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declBit(c+87,"dst_valid",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inst_IDU ");
    tracep->declBus(c+88,"XLEN",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+89,"ILEN",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBit(c+68,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+69,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+70,"inst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+77,"opcode",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+78,"funct3",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 2,0);
    tracep->declBus(c+79,"funct7",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+80,"rd",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+81,"rs1",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+82,"rs2",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declQuad(c+83,"imm",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("inst_RegFile ");
    tracep->declBus(c+88,"XLEN",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+89,"REG_CNT",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+90,"RID_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBit(c+68,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+69,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+87,"wr_en",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+80,"rd",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declQuad(c+85,"wdata",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declBus(c+81,"rs1",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+82,"rs2",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declQuad(c+73,"rs1_data",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declQuad(c+75,"rs2_data",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 63,0);
    tracep->declBus(c+3,"i",-1, FST_VD_IMPLICIT,FST_VT_VCD_INTEGER, false,-1, 31,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declQuad(c+4+i*2,"regfile",-1, FST_VD_IMPLICIT,FST_VT_SV_LOGIC, true,(i+0), 63,0);
    }
    tracep->popNamePrefix(2);
}

VL_ATTR_COLD void Vtop___024root__trace_init_top(Vtop___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_init_top\n"); );
    // Body
    Vtop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vtop___024root__trace_register(Vtop___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vtop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vtop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vtop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vtop___024root__trace_full_top_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vtop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vtop___024root__trace_full_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullQData(oldp+1,(vlSelf->top__DOT__PC),64);
    bufp->fullIData(oldp+3,(vlSelf->top__DOT__inst_RegFile__DOT__i),32);
    bufp->fullQData(oldp+4,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[0]),64);
    bufp->fullQData(oldp+6,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[1]),64);
    bufp->fullQData(oldp+8,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[2]),64);
    bufp->fullQData(oldp+10,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[3]),64);
    bufp->fullQData(oldp+12,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[4]),64);
    bufp->fullQData(oldp+14,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[5]),64);
    bufp->fullQData(oldp+16,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[6]),64);
    bufp->fullQData(oldp+18,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[7]),64);
    bufp->fullQData(oldp+20,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[8]),64);
    bufp->fullQData(oldp+22,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[9]),64);
    bufp->fullQData(oldp+24,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[10]),64);
    bufp->fullQData(oldp+26,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[11]),64);
    bufp->fullQData(oldp+28,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[12]),64);
    bufp->fullQData(oldp+30,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[13]),64);
    bufp->fullQData(oldp+32,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[14]),64);
    bufp->fullQData(oldp+34,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[15]),64);
    bufp->fullQData(oldp+36,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[16]),64);
    bufp->fullQData(oldp+38,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[17]),64);
    bufp->fullQData(oldp+40,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[18]),64);
    bufp->fullQData(oldp+42,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[19]),64);
    bufp->fullQData(oldp+44,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[20]),64);
    bufp->fullQData(oldp+46,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[21]),64);
    bufp->fullQData(oldp+48,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[22]),64);
    bufp->fullQData(oldp+50,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[23]),64);
    bufp->fullQData(oldp+52,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[24]),64);
    bufp->fullQData(oldp+54,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[25]),64);
    bufp->fullQData(oldp+56,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[26]),64);
    bufp->fullQData(oldp+58,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[27]),64);
    bufp->fullQData(oldp+60,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[28]),64);
    bufp->fullQData(oldp+62,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[29]),64);
    bufp->fullQData(oldp+64,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[30]),64);
    bufp->fullQData(oldp+66,(vlSelf->top__DOT__inst_RegFile__DOT__regfile[31]),64);
    bufp->fullBit(oldp+68,(vlSelf->clk));
    bufp->fullBit(oldp+69,(vlSelf->rst));
    bufp->fullIData(oldp+70,(vlSelf->inst),32);
    bufp->fullQData(oldp+71,(vlSelf->pc),64);
    bufp->fullQData(oldp+73,(vlSelf->top__DOT__inst_RegFile__DOT__regfile
                             [(0x1fU & (vlSelf->inst 
                                        >> 0xfU))]),64);
    bufp->fullQData(oldp+75,(vlSelf->top__DOT__inst_RegFile__DOT__regfile
                             [(0x1fU & (vlSelf->inst 
                                        >> 0x14U))]),64);
    bufp->fullCData(oldp+77,(vlSelf->top__DOT__opcode),7);
    bufp->fullCData(oldp+78,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->fullCData(oldp+79,((vlSelf->inst >> 0x19U)),7);
    bufp->fullCData(oldp+80,((0x1fU & (vlSelf->inst 
                                       >> 7U))),5);
    bufp->fullCData(oldp+81,((0x1fU & (vlSelf->inst 
                                       >> 0xfU))),5);
    bufp->fullCData(oldp+82,((0x1fU & (vlSelf->inst 
                                       >> 0x14U))),5);
    bufp->fullQData(oldp+83,(vlSelf->top__DOT__imm),64);
    bufp->fullQData(oldp+85,(vlSelf->top__DOT__dst),64);
    bufp->fullBit(oldp+87,(vlSelf->top__DOT__dst_valid));
    bufp->fullIData(oldp+88,(0x40U),32);
    bufp->fullIData(oldp+89,(0x20U),32);
    bufp->fullIData(oldp+90,(5U),32);
}
