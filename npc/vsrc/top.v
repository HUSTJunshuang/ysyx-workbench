`timescale 1ns/1ps

module top(
    input           clk,
    input           rst,
    input [1 : 0]   sw,
    output [15 : 0] led
);

    wire light;
    assign led = {16{light}};

    switch inst_switch(
        .a  (sw[0]),
        .b  (sw[1]),

        .f  (light)
    );

endmodule
