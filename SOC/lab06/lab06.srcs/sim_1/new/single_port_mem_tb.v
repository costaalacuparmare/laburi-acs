`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/08/2024 12:05:43 PM
// Design Name: 
// Module Name: single_port_mem_tb
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

// WRITE BEFORE READ TB
module single_port_mem_tb #(parameter biti = 32);
    reg clk, we;
    reg [2:0] addr;
    reg [biti-1:0] d_in;
    wire [biti-1:0] d_out;
    integer i;
    
    single_port_mem #(biti) inst1(clk, we, addr, d_in, d_out);
    
    always #10 clk = -clk;
    
    initial begin
        clk = 0; we = 0;
        d_in = {biti{1'bx}};
        addr = 3'bx;
        
        // Test scriere
        for (i = 0; i < 8; i = i + 1)
        begin
            @(negedge clk);
            #5 addr = i; we = 1; d_in = 15-i;
        end
        
        // Test citire
        @(negedge clk);
        for (i=0; i<8; i=i+1)
        begin
            @(negedge clk);
            #5 addr = i; we = 0;
        end
        
        
        @(negedge clk);
        #5 addr = 5; we = 1; d_in = 99;
        @(negedge clk);
        addr = 3'bx; we = 1'bx; d_in = {biti{1'bx}};
        @(negedge clk);
        $finish;
    end
endmodule
