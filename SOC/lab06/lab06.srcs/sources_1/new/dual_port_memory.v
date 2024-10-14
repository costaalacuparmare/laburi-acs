`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/08/2024 12:15:29 PM
// Design Name: 
// Module Name: dual_port_memory
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

// READ BEFORE WRITE
module dual_port_memory#(parameter biti = 32)(
    input clk, we_a, we_b,
    input [2:0] addr_a, addr_b,
    input [biti-1:0] d_in_a,
    input [biti-1:0] d_in_b,
    output [biti-1:0] d_out_a,
    output [biti-1:0] d_out_b
    );
    
    reg [2:0] read_addr_a;
    reg [2:0] read_addr_b;         
    reg [biti-1:0] ram_vec[7:0]; 
    reg [biti-1:0] read_bf_write_a;
    reg [biti-1:0] read_bf_write_b;
   
    always @(posedge clk) begin
        if(we_a) 
            ram_vec[addr_a] <= d_in_a;
        read_bf_write_a <= ram_vec[addr_a];
        read_addr_a <= addr_a;
    end
    
    assign d_out_a = read_bf_write_a;
    
    always @(posedge clk) begin
        if(we_b) 
            ram_vec[addr_b] <= d_in_b;
        read_bf_write_b <= ram_vec[addr_b];
        read_addr_b <= addr_b;
    end
    
    assign d_out_b = read_bf_write_b;
endmodule
