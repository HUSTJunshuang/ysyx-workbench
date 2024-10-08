`timescale 1ns/1ps

`include "inc/core.vh"

// include function from sim.cpp
import "DPI-C" function void set_nemu_state(input int state);

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
            // system opcode
            7'b11100_11: begin
                case (funct3)
                    3'b000: begin
                        if (imm[0]) begin   // ebreak
                            set_nemu_state(2);
                        end
                        else begin  // ecall
                        end
                    end
                    3'b001: begin   // csrrw
                    end
                    3'b010: begin   // csrrs
                    end
                    3'b011: begin   // csrrc
                    end
                    3'b101: begin   // csrrwi
                    end
                    3'b110: begin   // csrrsi
                    end
                    3'b111: begin   // csrrci
                    end
                    default: begin
                    end
                endcase
            end
            default: begin
                dst = 'h0;
                dst_valid = 1'b0;
            end
        endcase
    end

endmodule