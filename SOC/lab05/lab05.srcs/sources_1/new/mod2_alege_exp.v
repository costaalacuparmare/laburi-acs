`timescale 1ns / 1ps

module mod2_alege_exp(
    input [15:0] exp,
    output reg [7:0] chosen_exp
    );
    
    always @(*) begin
        if (exp[15:8] > exp[7:0]) begin
            assign chosen_exp = exp[15:8];
        end
        else begin
            assign chosen_exp = exp[7:0];
        end
    end
endmodule
