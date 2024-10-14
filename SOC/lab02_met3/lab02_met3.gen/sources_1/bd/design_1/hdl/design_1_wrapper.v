//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (win64) Build 3865809 Sun May  7 15:05:29 MDT 2023
//Date        : Wed Feb 28 14:13:08 2024
//Host        : ASUS-TUF-A15 running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (A,
    B,
    C,
    D,
    clk_0);
  input [0:0]A;
  input [0:0]B;
  input [0:0]C;
  output [0:0]D;
  input clk_0;

  wire [0:0]A;
  wire [0:0]B;
  wire [0:0]C;
  wire [0:0]D;
  wire clk_0;

  design_1 design_1_i
       (.A(A),
        .B(B),
        .C(C),
        .D(D),
        .clk_0(clk_0));
endmodule
