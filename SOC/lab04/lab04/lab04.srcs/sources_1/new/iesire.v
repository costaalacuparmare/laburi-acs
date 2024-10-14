`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/27/2024 02:16:23 PM
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
    input [3:0] sum0, sum1, sum2, sum3,
    output [15:0] sum
);

    assign sum[3:0] = sum0;
    assign sum[7:4] = sum1;
    assign sum[11:8] = sum2;
    assign sum[15:12] = sum3;
endmodule
