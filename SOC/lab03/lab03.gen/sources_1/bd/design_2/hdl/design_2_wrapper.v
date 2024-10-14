//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
//Date        : Wed Mar 29 13:16:40 2023
//Host        : DESKTOP-1FEJ3MB running 64-bit major release  (build 9200)
//Command     : generate_target design_2_wrapper.bd
//Design      : design_2_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_2_wrapper
   (An_0,
    DP_0,
    Seg_0,
    clk_in_0,
    clk_out_led_0,
    pauza_0,
    reset_0);
  output [7:0]An_0;
  output DP_0;
  output [6:0]Seg_0;
  input clk_in_0;
  output clk_out_led_0;
  input pauza_0;
  input reset_0;

  wire [7:0]An_0;
  wire DP_0;
  wire [6:0]Seg_0;
  wire clk_in_0;
  wire clk_out_led_0;
  wire pauza_0;
  wire reset_0;

  design_2 design_2_i
       (.An_0(An_0),
        .DP_0(DP_0),
        .Seg_0(Seg_0),
        .clk_in_0(clk_in_0),
        .clk_out_led_0(clk_out_led_0),
        .pauza_0(pauza_0),
        .reset_0(reset_0));
endmodule
