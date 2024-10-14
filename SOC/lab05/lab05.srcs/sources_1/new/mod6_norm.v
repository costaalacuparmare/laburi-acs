`timescale 1ns / 1ps

module mod6_norm(
    input [25:0] manti,
    output [8:0] val1,
    output [23:0] out
    );
    
    reg [8:0] aux = 0;
    reg [23:0] moved_manti;
    integer i;
    
    always @(*) begin
        aux = 0;
        if (manti[23]) begin
            moved_manti[22:0] = manti[23:1] << 1;
            moved_manti[23] = manti[24];
            aux[7:0] = 1;
            aux[8] = 0;
        end
        else begin
            aux[8] = 1;
            
            i = 23;
            while (manti[i] == 0) begin
                aux[7:0] = aux[7:0] + 1;
                i = i - 1;
            end
            
            moved_manti[22:0] = manti[23:0] << aux[7:0];
            moved_manti[23] = manti[24];
            if (aux[7:0])
                aux[7:0] = aux[7:0] - 1;
         end
    end
    
    assign out = moved_manti;
    assign val1 = aux;
endmodule
