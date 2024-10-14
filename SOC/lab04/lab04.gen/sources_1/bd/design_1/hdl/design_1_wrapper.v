//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (win64) Build 3865809 Sun May  7 15:05:29 MDT 2023
//Date        : Wed Apr 10 11:41:57 2024
//Host        : ASUS-TUF-A15 running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (a_0,
    b_0,
    c4_0,
    carry_in_0,
    sum_0);
  input [15:0]a_0;
  input [15:0]b_0;
  output c4_0;
  input carry_in_0;
  output [15:0]sum_0;

  wire [15:0]a_0;
  wire [15:0]b_0;
  wire c4_0;
  wire carry_in_0;
  wire [15:0]sum_0;

  design_1 design_1_i
       (.a_0(a_0),
        .b_0(b_0),
        .c4_0(c4_0),
        .carry_in_0(carry_in_0),
        .sum_0(sum_0));
endmodule
