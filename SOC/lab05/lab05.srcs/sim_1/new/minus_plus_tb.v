`timescale 1ns / 1ps


module minus_plus_tb();
    reg [31:0] ter1;
    reg [31:0] ter2;
    reg clk, load, clear, op;
    wire [31:0] out;
    
    minus_plus modul(clk, load, clear, op, ter1, ter2, out);
    
    always begin
        #5 clk = ~clk; load = ~load;
    end
    
    initial begin
        clk = 1;
        load = 1;
        clear = 0;
        
        // INIT
        ter1 = 32'h0;
        ter2 = 32'h0;
        op = 0;
        
        
        #10
        // 17.13 + 19.81 = 36,94
        ter1 = 32'h41890a3d;
        ter2 = 32'h419e7ae1;
        op = 0;
        
        #10
        // 30.15 + 47.54 = 77,72
        ter1 = 32'h41f13333;
        ter2 = 32'h423e28f6;
        op = 0;
        
        // 245.88 - 57.27  = 188,61
        #10
        ter1 = 32'h4375e148;
        ter2 = 32'h4265147b;
        op = 1;
        
        // 139.27 - 29.15 = 110.12
        #10
        ter1 = 32'h430b451f;
        ter2 = 32'h41e93333;
        op = 1;
        
        
     end
endmodule
