`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 05/22/2024 11:28:55 AM
// Design Name: 
// Module Name: vending_machine_tb
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

`timescale 1ns / 1ps

module tb_vending_machine;

    // Declara?iile de semnale pentru a se conecta la modulul de vending machine
    reg clk;
    reg reset;
    reg [7:0] inputs;
    wire product1_selected;
    wire product2_selected;
    wire product3_selected;
    wire change_50bani;
    wire change_1leu;
    wire insufficient_funds;
    wire cash_overflow;

    // Instan?ierea modulului de vending machine
    vending_machine uut (
        clk,
        reset,
        inputs,
        product1_selected,
        product2_selected,
        product3_selected,
        change_50bani,
        change_1leu,
        insufficient_funds,
        cash_overflow
    );

    // Generare semnal de ceas
    always #5 clk = ~clk;

    initial begin
        // Ini?ializare semnale
        clk = 0;
        reset = 0;
        inputs = 8'b0;

        // Resetare modul
        reset = 1;
        #10;
        reset = 0;
        #10;

        // Testare ad?ugare monede ?i bancnote
        inputs = 8'b10000000; // Adaug? 5 bani
        #10;
        inputs = 8'b01000000; // Adaug? 10 bani
        #10;
        inputs = 8'b00100000; // Adaug? 50 bani
        #10;
        inputs = 8'b00010000; // Adaug? 1 leu
        #10;

        // Testare achizi?ionare produs 1 (cost 25 bani)
        inputs = 8'b00001000;
        #10;
        inputs = 8'b0;
        #10;

        // Testare achizi?ionare produs 2 (cost 30 bani)
        inputs = 8'b00000100;
        #10;
        inputs = 8'b0;
        #10;

        // Testare achizi?ionare produs 3 (cost 50 bani)
        inputs = 8'b00000010;
        #10;
        inputs = 8'b0;
        #10;

        // Testare rest
        inputs = 8'b00000001; // Solicit? rest
        #10;
        inputs = 8'b0;
        #50; // A?teptare pentru distribuirea restului

        // Testare overflow de bani
        inputs = 8'b00010000; // Adaug? 1 leu
        #10;
        inputs = 8'b00010000; // Adaug? 1 leu
        #10;
        inputs = 8'b00010000; // Adaug? 1 leu
        #10;

        // Încheiere test
      //  $stop;
    end
endmodule
