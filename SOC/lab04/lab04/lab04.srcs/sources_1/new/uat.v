`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/27/2024 02:26:05 PM
// Design Name: 
// Module Name: uat
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


module uat(c0, p0, g0, p1, g1, p2, g2, p3, g3, c1, c2, c3, c4);
    input c0, p0, g0, p1, g1, p2, g2, p3, g3;
    output c1, c2, c3, c4;
    
    assign c1 = g0 ^ p0 & c0;
    assign c2 = g1 ^ p1 & g0 ^ p1 & p0 & c0;
    assign c3 = g2 ^ p2 & g1 ^ p2 & p1 & g0 ^ p2 & p1 & p0 & c0;
    assign c4 = g3 ^ p3 & g2 ^ p3 & p2 & g1 ^ p3 & p2 & p1 & g0 ^ p3 & p2 & p1 & p0 & c0;
endmodule
