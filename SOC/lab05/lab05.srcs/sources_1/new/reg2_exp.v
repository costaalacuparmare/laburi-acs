`timescale 1ns / 1ps

module reg2_exp(
    input [7:0] exp,
    input clk,
    input load,
    input clear,
    output reg [7:0] out
    );
    
    always @(posedge clk)
        if (clear)
           out <= 0;
        else if (load)
           out <= exp;
endmodule
