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


module sumator4b(a, b, carry_in, sum, G, P, carry_out);
    input [3:0] a, b;
    input carry_in;
    output [3:0] sum;
    output G, P, carry_out;
    wire [3:0] p, g, c;
    
    assign p = a ^ b;
    assign g = a & b;
    
    uat set(carry_in, p[0], g[0], p[1], g[1], p[2], g[2], p[3], g[3], c[1], c[2], c[3], carry_out, P, G);
    assign c[0] = carry_in;
    assign sum = p ^ c;
endmodule
