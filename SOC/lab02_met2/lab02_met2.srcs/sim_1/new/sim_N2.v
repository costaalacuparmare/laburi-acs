`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/13/2024 12:50:34 PM
// Design Name: 
// Module Name: sim_N2
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
module sim_N2( );
    reg A, B, C; //intotdeuna la simulare intrarile vor fi declarate ca si reg
    wire D; //intotdeauna iesirea in catul simularii va fi de tip vire
    reg [8*100:1] olinie;
    integer fd, count, status, i_A, i_B, i_C, i_D, erori;

    design_1_wrapper instance2(A, B, C, D); //instantierea modulului care ne va furnize rezultatul dorit

    initial begin
        A = 1'bx; B = 1'bx; C = 1'bx;
        fd = $fopen("../../input.txt", "r");
        if (fd==0)
            fd = $fopen("../../../input.txt","r");
        count = 1;
        #100
        erori = 0;
        while ($fgets(olinie, fd))
        begin
            status = $sscanf(olinie, "%d %d %d %d", i_A, i_B, i_C, i_D);
            A = i_A; B = i_B; C = i_C;
            #50
            if (i_D == D)
                $display("%d(%t) ok, A=%d, B=%d, C=%d, D=%d\n", count, $time, A, B, C, D); //stime in ps
            else begin
                erori = erori+1;
                $display("%d(%t):EROARE, A=%d, B=%d, C=%d, D(actual)=%d, D(corect)=%d", count, $time,
                    A, B, C, D, i_A);
            end
            count = count + 1;
        end
        #50 A = 1'bx; B = 1'bx; C = 1'bx;
        #50 $stop;
        #50 $finish;
    end
endmodule


