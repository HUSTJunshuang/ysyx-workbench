`timescale 1ns/1ps

`include "inc/core.vh"

module top #(
    parameter XLEN = `ysyx_24090011_XLEN,
    parameter ILEN = `ysyx_24090011_ILEN
) (
    input                   clk,
    input                   rst,
    input [ILEN - 1 : 0]    inst,
    output [XLEN - 1 : 0]   pc
);

    reg [XLEN - 1 : 0] PC;
    assign pc = PC;
    // RegisterFile
    wire [XLEN - 1 : 0] src1, src2;
    // IDU
    wire [6 : 0] opcode;
    wire [2 : 0] funct3;
    wire [6 : 0] funct7;
    wire [4 : 0] rd, rs1, rs2;
    wire [XLEN - 1 : 0] imm;
    // EXU
    wire [XLEN - 1 : 0] dst;
    wire dst_valid;

    always @(posedge clk) begin
        if (rst) begin
            PC <= `ysyx_24090011_XLEN'h80000000;
        end
        else begin
            PC <= PC + 'h1;
        end
    end

    `JJS_STUID``_RegisterFile inst_RegFile(
        .clk        (clk),
        .rst        (rst),
        .wr_en      (dst_valid),
        .rd         (rd),
        .wdata      (dst),
        .rs1        (rs1),
        .rs2        (rs2),
        .rs1_data   (src1),
        .rs2_data   (src2)
    );

    `JJS_STUID``_IDU inst_IDU(
        .clk    (clk),
        .rst    (rst),
        .inst   (inst),
        .opcode (opcode),
        .funct3 (funct3),
        .funct7 (funct7),
        .rd     (rd),
        .rs1    (rs1),
        .rs2    (rs2),
        .imm    (imm)
    );

    `JJS_STUID``_EXU inst_EXU(
        .clk        (clk),
        .rst        (rst),
        .opcode     (opcode),
        .funct3     (funct3),
        .funct7     (funct7),
        .src1       (src1),
        .src2       (src2),
        .imm        (imm),
        .dst        (dst),
        .dst_valid  (dst_valid)
    );

endmodule
