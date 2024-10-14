//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (win64) Build 3865809 Sun May  7 15:05:29 MDT 2023
//Date        : Wed Apr 10 11:41:57 2024
//Host        : ASUS-TUF-A15 running 64-bit major release  (build 9200)
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=7,numReposBlks=7,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=7,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
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

  wire [15:0]a_0_1;
  wire [15:0]b_0_1;
  wire carry_in_0_1;
  wire [15:0]iesire_0_sum;
  wire [3:0]intrare_0_a0;
  wire [3:0]intrare_0_a1;
  wire [3:0]intrare_0_a2;
  wire [3:0]intrare_0_a3;
  wire [3:0]intrare_0_b0;
  wire [3:0]intrare_0_b1;
  wire [3:0]intrare_0_b2;
  wire [3:0]intrare_0_b3;
  wire sumator4b_0_G;
  wire sumator4b_0_P;
  wire [3:0]sumator4b_0_sum;
  wire sumator4b_1_G;
  wire sumator4b_1_P;
  wire [3:0]sumator4b_1_sum;
  wire sumator4b_2_G;
  wire sumator4b_2_P;
  wire [3:0]sumator4b_2_sum;
  wire sumator4b_3_G;
  wire sumator4b_3_P;
  wire [3:0]sumator4b_3_sum;
  wire uat_0_c1;
  wire uat_0_c2;
  wire uat_0_c3;
  wire uat_0_c4;

  assign a_0_1 = a_0[15:0];
  assign b_0_1 = b_0[15:0];
  assign c4_0 = uat_0_c4;
  assign carry_in_0_1 = carry_in_0;
  assign sum_0[15:0] = iesire_0_sum;
  design_1_iesire_0_0 iesire_0
       (.sum(iesire_0_sum),
        .sum0(sumator4b_0_sum),
        .sum1(sumator4b_1_sum),
        .sum2(sumator4b_2_sum),
        .sum3(sumator4b_3_sum));
  design_1_intrare_0_0 intrare_0
       (.a(a_0_1),
        .a0(intrare_0_a0),
        .a1(intrare_0_a1),
        .a2(intrare_0_a2),
        .a3(intrare_0_a3),
        .b(b_0_1),
        .b0(intrare_0_b0),
        .b1(intrare_0_b1),
        .b2(intrare_0_b2),
        .b3(intrare_0_b3));
  design_1_sumator4b_0_0 sumator4b_0
       (.G(sumator4b_0_G),
        .P(sumator4b_0_P),
        .a(intrare_0_a0),
        .b(intrare_0_b0),
        .carry_in(carry_in_0_1),
        .sum(sumator4b_0_sum));
  design_1_sumator4b_1_0 sumator4b_1
       (.G(sumator4b_1_G),
        .P(sumator4b_1_P),
        .a(intrare_0_a1),
        .b(intrare_0_b1),
        .carry_in(uat_0_c1),
        .sum(sumator4b_1_sum));
  design_1_sumator4b_2_0 sumator4b_2
       (.G(sumator4b_2_G),
        .P(sumator4b_2_P),
        .a(intrare_0_a2),
        .b(intrare_0_b2),
        .carry_in(uat_0_c2),
        .sum(sumator4b_2_sum));
  design_1_sumator4b_3_0 sumator4b_3
       (.G(sumator4b_3_G),
        .P(sumator4b_3_P),
        .a(intrare_0_a3),
        .b(intrare_0_b3),
        .carry_in(uat_0_c3),
        .sum(sumator4b_3_sum));
  design_1_uat_0_0 uat_0
       (.c0(carry_in_0_1),
        .c1(uat_0_c1),
        .c2(uat_0_c2),
        .c3(uat_0_c3),
        .c4(uat_0_c4),
        .g0(sumator4b_0_G),
        .g1(sumator4b_1_G),
        .g2(sumator4b_2_G),
        .g3(sumator4b_3_G),
        .p0(sumator4b_0_P),
        .p1(sumator4b_1_P),
        .p2(sumator4b_2_P),
        .p3(sumator4b_3_P));
endmodule
