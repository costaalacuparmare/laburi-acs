`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 5/20/2024 11:20:54 PM
// Design Name: 
// Module Name: mijloc
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


module mijloc(
    input Gk,
    input Pk,
    input Gkm1,
    input Pkm1,
    output Go,
    output Po
    );
    
    assign Po = Pk & Pkm1;
    assign Go = Gk | (Pk & Gkm1);
endmodule
