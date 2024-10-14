`timescale 1ns / 1ps

module reg1_exps(
    input [15:0] exp,
    input clk,
    input load,
    input clear,
    output reg [15:0] out
    );
    
    always @(posedge clk)
        if (clear)
           out <= 0;
        else if (load)
           out <= exp;
endmodule
