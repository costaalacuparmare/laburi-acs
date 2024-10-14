`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/15/2023 02:07:09 PM
// Design Name: 
// Module Name: sim_num_0
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


module sim_num_0( );
    reg reset_0;
    reg pauza_0; 
    reg clk_out_led_0;
    wire carry_out_0;
    wire [5:0]valoare_bin_0;
    cronometru num(carry_out_0,
    clk_out_led_0,
    pauza_0,
    reset_0,
    valoare_bin_0);
    
    always #5 clk_out_led_0 = ~clk_out_led_0;
    initial begin
        clk_out_led_0 = 0;
        reset_0 = 0;
        pauza_0 = 0;
        #5 reset_0 = 1;
        #5 reset_0 = 0;
        #50 pauza_0 = 1;
        #50 pauza_0 = 0;
    end 
endmodule
