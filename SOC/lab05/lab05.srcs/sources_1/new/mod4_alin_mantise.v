`timescale 1ns / 1ps

module mod4_alin_mantise(
    input [56:0] manti,
    output reg [47:0] out
    );
    
    reg [23:0] aux1;
    reg [23:0] aux2;
    
    always @(*) begin
        if (manti[56] == 0) begin
            aux1[23] = manti[47];
            aux1[22:0] = {1'b1, manti[46:25]};
            aux1[22:0] = aux1[22:0] >> manti[55:48];
            
            aux2[23] = manti[23];
            aux2[22:0] = {1'b1, manti[22:1]};
        end
        else begin
            aux2[23] = manti[23];
            aux2[22:0] = {1'b1, manti[22:1]};
            aux2[22:0] = aux2[22:0] >> manti[55:48];
            
            aux1[23] = manti[47];
            aux1[22:0] = {1'b1, manti[46:25]};
        end
        
        assign out = {aux1, aux2};
    end
endmodule
