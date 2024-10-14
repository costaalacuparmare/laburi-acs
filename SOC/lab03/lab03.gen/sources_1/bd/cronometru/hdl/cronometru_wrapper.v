//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
//Date        : Wed Mar 13 15:05:34 2024
//Host        : DESKTOP-G7899NP running 64-bit major release  (build 9200)
//Command     : generate_target cronometru_wrapper.bd
//Design      : cronometru_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module cronometru_wrapper
   (carry_out_0,
    clk_out_led_0,
    pauza_0,
    reset_0,
    valoare_bin_0);
  output carry_out_0;
  input clk_out_led_0;
  input pauza_0;
  input reset_0;
  output [5:0]valoare_bin_0;

  wire carry_out_0;
  wire clk_out_led_0;
  wire pauza_0;
  wire reset_0;
  wire [5:0]valoare_bin_0;

  cronometru cronometru_i
       (.carry_out_0(carry_out_0),
        .clk_out_led_0(clk_out_led_0),
        .pauza_0(pauza_0),
        .reset_0(reset_0),
        .valoare_bin_0(valoare_bin_0));
endmodule
