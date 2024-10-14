`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 5/20/2024 11:25:23 PM
// Design Name: 
// Module Name: iesire
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


module iesire(
    input A,
    input B,
    input G,
    output S
    );
    
    assign S = (A ^ B) ^ G;
endmodule
