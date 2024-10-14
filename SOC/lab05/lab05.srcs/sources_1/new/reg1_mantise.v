`timescale 1ns / 1ps

module reg1_mantise(
    input [47:0] manti,
    input clk,
    input load,
    input clear,
    output reg [47:0] out
    );
    
    always @(posedge clk)
        if (clear)
           out <= 0;
        else if (load)
           out <= manti;
endmodule
