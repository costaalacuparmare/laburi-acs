`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 5/20/2024 10:37:03 PM
// Design Name: 
// Module Name: intrare
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


module intrare(
    input A,
    input B,
    output G,
    output P
    );
    
    assign G = A & B;
    assign P = A | B;
endmodule
