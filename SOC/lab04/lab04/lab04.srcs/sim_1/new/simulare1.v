`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/27/2024 03:01:13 PM
// Design Name: 
// Module Name: simulare
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


module simulation( );
    
    reg [15:0]a_0;
    reg [15:0]b_0;
    wire c4_0;
    reg carry_in_0;
    wire [15:0]sum_0;

    design_1_wrapper sumator16b(a_0,
    b_0,
    c4_0,
    carry_in_0,
    sum_0
       
    );
    
    initial begin
      a_0 = 320; b_0 = 290;
      carry_in_0 = 0;
    end
endmodule
