`timescale 1ns/1ps

`include "inc/core.v"

module `JJS_STUID``_IDU #(
    parameter XLEN = `ysyx_24090011_XLEN,
    parameter ILEN = `ysyx_24090011_ILEN
) (
    input                       clk,
    input                       rst,
    input [ILEN - 1 : 0]        inst,
    // input                       inst_valid,
    output reg [6 : 0]          opcode,
    output reg [2 : 0]          funct3,
    output reg [6 : 0]          funct7,
    output reg [4 : 0]          rd,
    output reg [4 : 0]          rs1,
    output reg [4 : 0]          rs2,
    output reg [XLEN - 1 : 0]   imm
);

    /* opcode classification */
    // R-type: 01100 11
    // I-type: 00000 11 or 00100 11 or 11001 11
    // S-type: 01000 11
    // B-type: 11000 11
    // U-type: 00101 11 or 01101 11
    // J-type: 11011 11

    always @(*) begin
        opcode = inst[6 : 0];
        funct3 = inst[14 : 12];
        funct7 = inst[31 : 25];
        rd = inst[11 : 7];
        rs1 = inst[19 : 15];
        rs2 = inst[24 : 20];

        case (opcode)
            7'b01100_11: begin  // R-type
                imm = 'h0;
            end
            7'b00000_11, 7'b00100_11, 7'b11001_11: begin    // I-type
                imm = {{(XLEN - 12){inst[31]}}, inst[31 : 20]};
            end
            7'b01000_11: begin  // S-type
                imm = {{(XLEN - 12){inst[31]}}, inst[31 : 25], inst[11 : 7]};
            end
            7'b11000_11: begin  // B-type
                imm = {{(XLEN - 12){inst[31]}}, inst[7], inst[30 : 25], inst[11 : 8], 1'b0};
            end
            7'b00101_11, 7'b01101_11: begin // U-type
                imm = {{(XLEN - 31){inst[31]}}, inst[30 : 12], 12'h0};
            end
            7'b11011_11: begin  // J-type
                imm = {{(XLEN - 20){inst[31]}}, inst[19 : 12], inst[20], inst[30 : 21], 1'b0};
            end
            default: begin
                imm = 'h0;
            end
        endcase
    end

endmodule
