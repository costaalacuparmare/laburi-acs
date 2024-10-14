//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
//Date        : Wed Mar 13 15:05:34 2024
//Host        : DESKTOP-G7899NP running 64-bit major release  (build 9200)
//Command     : generate_target cronometru.bd
//Design      : cronometru
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "cronometru,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=cronometru,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=1,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "cronometru.hwdef" *) 
module cronometru
   (carry_out_0,
    clk_out_led_0,
    pauza_0,
    reset_0,
    valoare_bin_0);
  output carry_out_0;
  input clk_out_led_0;
  input pauza_0;
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET_0 RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET_0, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input reset_0;
  output [5:0]valoare_bin_0;

  wire clk_out_led_0_1;
  wire numarator_59_0_0_carry_out;
  wire [5:0]numarator_59_0_0_valoare_bin;
  wire pauza_0_1;
  wire reset_0_1;

  assign carry_out_0 = numarator_59_0_0_carry_out;
  assign clk_out_led_0_1 = clk_out_led_0;
  assign pauza_0_1 = pauza_0;
  assign reset_0_1 = reset_0;
  assign valoare_bin_0[5:0] = numarator_59_0_0_valoare_bin;
  cronometru_numarator_59_0_0_0 numarator_59_0_0
       (.carry_out(numarator_59_0_0_carry_out),
        .clk_out_led(clk_out_led_0_1),
        .pauza(pauza_0_1),
        .reset(reset_0_1),
        .valoare_bin(numarator_59_0_0_valoare_bin));
endmodule
