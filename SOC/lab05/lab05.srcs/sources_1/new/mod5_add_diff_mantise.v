`timescale 1ns / 1ps

module mod5_add_diff_mantise(
    input op,
    input [47:0] manti,
    output [25:0] out
    );
    
    reg [25:0] aux;
    reg sign1;
    reg sign2;

    always @(*) begin
        sign1 = manti[47];
        sign2 = manti[23];
        
        if (op == 1)
            sign2 = ~sign2;
        
        if (sign1 == sign2) begin
            aux[23:0] = manti[46:24] + manti[22:0];
            aux[24] = sign1;
        end
        else begin
            if (manti[46:24] > manti[22:0]) begin
                aux[23:0] = manti[46:24] - manti[22:0];
                aux[24] = sign1;
            end
            else begin
                aux[23:0] = manti[22:0] -  manti[46:24];
                aux[24] = sign2;
            end
        end
        
        if (aux[23:0] != 0)
            aux[25] = 0;
        else
            aux[25] = 1;
    end
    
    assign out = aux[25:0];
endmodule
