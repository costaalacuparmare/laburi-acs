`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/15/2023 12:58:11 PM
// Design Name: 
// Module Name: numarator_59_0
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


module numarator_59_0(
    input reset, pauza, clk_out_led,
    output[5:0] valoare_bin, 
    output reg carry_out
    );
    
    reg[5:0] counter= 6'd0;
    reg[0:0] carry = 1'd0;
    
    always @(posedge clk_out_led or posedge reset)
    begin
       carry_out = 1'b0;
           if (reset)
                counter <= 0;
           else  if (!pauza) begin
                     if (counter == 59) begin
                        counter <= 0;
                        carry_out <= 1'b1;
                    end else
                        counter <= counter + 1;
      
           end
   end
  
    assign valoare_bin = counter;
endmodule