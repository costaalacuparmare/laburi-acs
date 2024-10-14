`timescale 1ns / 1ps

module mod7_concat(
    input [47:0] manti,
    input [8:0] val1,
    output [56:0] out
    );
    
    assign out = {val1, manti};
endmodule
