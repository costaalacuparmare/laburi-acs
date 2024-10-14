//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
//Date        : Wed Mar 29 13:16:40 2023
//Host        : DESKTOP-1FEJ3MB running 64-bit major release  (build 9200)
//Command     : generate_target design_2.bd
//Design      : design_2
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_2,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_2,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=6,numReposBlks=6,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=6,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_2.hwdef" *) 
module design_2
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
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 RST.RESET_0 RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME RST.RESET_0, INSERT_VIP 0, POLARITY ACTIVE_LOW" *) input reset_0;

  wire [7:0]afisare_7seg_0_0_An;
  wire afisare_7seg_0_0_DP;
  wire [6:0]afisare_7seg_0_0_Seg;
  wire [3:0]bin2bcd_0_0_BCD0;
  wire [3:0]bin2bcd_0_0_BCD1;
  wire [3:0]bin2bcd_0_1_BCD0;
  wire [3:0]bin2bcd_0_1_BCD1;
  wire clk_in_0_1;
  wire divizor_ceas_0_clk_out_led;
  wire divizor_ceas_0_clk_out_seg;
  wire numarator_59_0_0_carry_out;
  wire [5:0]numarator_59_0_0_valoare_bin;
  wire [5:0]numarator_59_0_1_valoare_bin;
  wire pauza_0_1;
  wire reset_0_1;

  assign An_0[7:0] = afisare_7seg_0_0_An;
  assign DP_0 = afisare_7seg_0_0_DP;
  assign Seg_0[6:0] = afisare_7seg_0_0_Seg;
  assign clk_in_0_1 = clk_in_0;
  assign clk_out_led_0 = divizor_ceas_0_clk_out_led;
  assign pauza_0_1 = pauza_0;
  assign reset_0_1 = reset_0;
  design_2_afisare_7seg_0_0_0 afisare_7seg_0_0
       (.An(afisare_7seg_0_0_An),
        .BCD0(bin2bcd_0_0_BCD0),
        .BCD1(bin2bcd_0_0_BCD1),
        .BCD2(bin2bcd_0_1_BCD0),
        .BCD3(bin2bcd_0_1_BCD1),
        .DP(afisare_7seg_0_0_DP),
        .Seg(afisare_7seg_0_0_Seg),
        .clk_out_seg(divizor_ceas_0_clk_out_seg),
        .reset(reset_0_1));
  design_2_bin2bcd_0_0_0 bin2bcd_0_0
       (.BCD0(bin2bcd_0_0_BCD0),
        .BCD1(bin2bcd_0_0_BCD1),
        .valoare_bin(numarator_59_0_1_valoare_bin));
  design_2_bin2bcd_0_1_0 bin2bcd_0_1
       (.BCD0(bin2bcd_0_1_BCD0),
        .BCD1(bin2bcd_0_1_BCD1),
        .valoare_bin(numarator_59_0_0_valoare_bin));
  design_2_divizor_ceas_0_0 divizor_ceas_0
       (.clk_in(clk_in_0_1),
        .clk_out_led(divizor_ceas_0_clk_out_led),
        .clk_out_seg(divizor_ceas_0_clk_out_seg),
        .reset(reset_0_1));
  design_2_numarator_59_0_0_0 numarator_59_0_0
       (.carry_out(numarator_59_0_0_carry_out),
        .clk_out_led(divizor_ceas_0_clk_out_led),
        .pauza(pauza_0_1),
        .reset(reset_0_1),
        .valoare_bin(numarator_59_0_0_valoare_bin));
  design_2_numarator_59_0_1_0 numarator_59_0_1
       (.clk_out_led(numarator_59_0_0_carry_out),
        .pauza(pauza_0_1),
        .reset(reset_0_1),
        .valoare_bin(numarator_59_0_1_valoare_bin));
endmodule
