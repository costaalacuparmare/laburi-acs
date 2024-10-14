`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/20/2024 02:15:46 PM
// Design Name: 
// Module Name: test
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test(

    );
    reg [15:0] A, B;
    reg C;
    wire[15:0] Rezultat;
    sumator sumator(A, B, C, Rezultat);
    initial begin
    C = 0;
    A = 1241;
    B = 4211;
    #40
    C = 0;
    A = 4421;
    B = 9999;
    #40
    C = 0;
    A = -5004;
    B = 10000;
    #40
    $finish;
    end
endmodule
