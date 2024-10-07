`timescale 1ns/1ps

`include "inc/core.vh"

module `JJS_STUID``_EXU #(
    parameter XLEN = `ysyx_24090011_XLEN
) (
    input                       clk,
    input                       rst,
    input [6 : 0]               opcode,
    input [2 : 0]               funct3,
    input [6 : 0]               funct7,
    input [XLEN - 1 : 0]        src1,
    input [XLEN - 1 : 0]        src2,
    input [XLEN - 1 : 0]        imm,
    output reg [XLEN - 1 : 0]   dst,
    output reg                  dst_valid
);

    always @(*) begin
        case (opcode)
            7'b00100_11: begin
                case (funct3)
                    3'b000: begin
                        dst = src1 + imm;
                        dst_valid = 1'b1;
                    end
                    default: begin
                        dst = 'h0;
                        dst_valid = 1'b0;
                    end
                endcase
            end
            default: begin
                dst = 'h0;
            end
        endcase
    end

endmodule