`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/27/2024 01:53:00 PM
// Design Name: 
// Module Name: sumator4b
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


module sumator4b(a, b, carry_in, sum, G, P);
    input [3:0] a, b;
    input carry_in;
    output [3:0] sum;
    output G, P;
    wire [3:0] p, g, c;
    
    assign p = a ^ b;
    assign g = a & b;
    
    assign P = p[3] & p[2] & p[1] & p[0];
    assign G = g[3] | (p[3] & g[2]) | (p[3] & p[2] & g[1]) | (p[3] & p[2] & p[1] & g[0]);
    assign c[0] = carry_in;
    assign c[1] = g[0] | (p[0] & c[0]);
    assign c[2] = g[1] | (p[1] & g[0]) | p[1] & p[0] & c[0];
    assign c[3] = g[2] | (p[2] & g[1]) | (p[2] & p[1] & g[0]) | p[2] & p[1] & p[0] & c[0];
    assign sum = p ^ c;
endmodule
