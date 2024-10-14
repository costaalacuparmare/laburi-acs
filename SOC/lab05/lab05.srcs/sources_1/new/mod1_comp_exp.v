`timescale 1ns / 1ps


module mod1_comp_exp(
    input [15:0] exp,
    output reg [8:0] val1,
    output [15:0] comp_exp
    );
    
    always @(*) begin
        if (exp[15:8] > exp[7:0]) begin
            val1[8] = 1;
            val1[7:0] = exp[15:8] - exp[7:0];
        end
        else begin
            val1[8] = 0;
            val1[7:0] = exp[7:0] - exp[15:8];
        end
    end
    
    assign comp_exp = exp;
endmodule
