`timescale 1ns/1ps

`include "inc/core.vh"

module `JJS_STUID``_IFU #(
    parameter XLEN = `ysyx_24090011_XLEN,
    parameter ILEN = `ysyx_24090011_ILEN
) (
    input                       clk,
    input                       rst,
    input [XLEN - 1 : 0]        pc,
    output reg [ILEN - 1 : 0]   inst,
    output reg                  valid   // need valid signal to avoid error when inst cache missing
);

    // no logic now

endmodule
