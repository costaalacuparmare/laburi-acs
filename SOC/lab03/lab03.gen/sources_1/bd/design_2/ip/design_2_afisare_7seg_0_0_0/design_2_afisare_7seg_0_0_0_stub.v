// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
// Date        : Wed Mar 29 13:17:21 2023
// Host        : DESKTOP-1FEJ3MB running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/Users/student/laborator_324CB/lab_2/lab3_324CB/lab3_324CB.gen/sources_1/bd/design_2/ip/design_2_afisare_7seg_0_0_0/design_2_afisare_7seg_0_0_0_stub.v
// Design      : design_2_afisare_7seg_0_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "afisare_7seg_0,Vivado 2022.1" *)
module design_2_afisare_7seg_0_0_0(clk_out_seg, reset, BCD0, BCD1, BCD2, BCD3, An, Seg, DP)
/* synthesis syn_black_box black_box_pad_pin="clk_out_seg,reset,BCD0[3:0],BCD1[3:0],BCD2[3:0],BCD3[3:0],An[7:0],Seg[6:0],DP" */;
  input clk_out_seg;
  input reset;
  input [3:0]BCD0;
  input [3:0]BCD1;
  input [3:0]BCD2;
  input [3:0]BCD3;
  output [7:0]An;
  output [6:0]Seg;
  output DP;
endmodule
