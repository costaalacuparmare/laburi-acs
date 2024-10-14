`timescale 1ns / 1ps


module get_op(
    input op,
    input clk,
    input load,
    input clear,
    output reg out
    );
    
    always @(posedge clk)
        if (clear)
           out <= 0;
        else if (load)
           out <= op;
endmodule