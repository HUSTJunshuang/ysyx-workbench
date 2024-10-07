`timescale 1ns/1ps

`include "inc/core.v"

module `JJS_STUID``_RegisterFile #(
    parameter XLEN = `ysyx_24090011_XLEN,
    parameter REG_CNT = 32,
    parameter RID_WIDTH = 5
) (
    input                       clk,
    input                       rst,
    input                       wr_en,
    input [RID_WIDTH - 1 : 0]   rd,
    input [XLEN - 1 : 0]        wdata,
    input [RID_WIDTH - 1 : 0]   rs1,
    input [RID_WIDTH - 1 : 0]   rs2,
    output [XLEN - 1 : 0]       rs1_data,
    output [XLEN - 1 : 0]       rs2_data
);

    integer i;

    reg [XLEN - 1 : 0] regfile [REG_CNT - 1 : 0];
    assign regfile[0] = 'h0;    // reg x0 is hardwired to 0

    // read reg
    assign rs1_data = regfile[rs1];
    assign rs2_data = regfile[rs2];

    // write reg
    always @(posedge clk) begin
        if (rst) begin
            for (i = 1; i < REG_CNT; i = i + 1) begin
                regfile[i] <= 'h0;
            end
        end
        else if (wr_en && rd != 'h0) begin
            regfile[rd] <= wdata;
        end
    end

endmodule
