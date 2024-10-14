`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/27/2024 02:10:47 PM
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
    input [15:0] a,
    input [15:0] b,
    output [3:0] a0,
    output [3:0] a1,
    output [3:0] a2,
    output [3:0] a3,
    output [3:0] b0,
    output [3:0] b1,
    output [3:0] b2,
    output [3:0] b3
);

    assign a0 = a[3:0];
    assign a1 = a[7:4];
    assign a2 = a[11:8];
    assign a3 = a[15:12];
    
    assign b0 = b[3:0];
    assign b1 = b[7:4];
    assign b2 = b[11:8];
    assign b3 = b[15:12];
endmodule
