`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/08/2024 11:53:28 AM
// Design Name: 
// Module Name: single_port_mem
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

// WRITE BEFORE READ
module single_port_mem #(parameter biti = 32) (
        input clk, we,
        input [2:0] addr,
        input [biti-1:0] d_in,
        output [biti-1:0] d_out
    );
    
    reg [2:0] read_addr;
    reg [biti-1:0] ram_vec[7:0];
    
    always @(posedge clk) begin
        if (we)
            ram_vec[addr] <= d_in;
        read_addr <= addr;
    end
    
endmodule
