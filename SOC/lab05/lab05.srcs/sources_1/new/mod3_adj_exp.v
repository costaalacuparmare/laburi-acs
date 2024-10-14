`timescale 1ns / 1ps


module mod3_adj_exp(
    input [7:0] exp,
    input [8:0] val2,
    output [7:0] out
    );
    
    reg [7:0] aux;
    
    always @(*) begin
        if (val2[8] == 0) begin
            aux = exp + 1;
        end
        else begin
            aux = exp - val2[7:0];
        end
    end
    
    assign out = aux;
endmodule
