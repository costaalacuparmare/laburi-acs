//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2023.1 (win64) Build 3865809 Sun May  7 15:05:29 MDT 2023
//Date        : Wed Feb 28 14:13:08 2024
//Host        : ASUS-TUF-A15 running 64-bit major release  (build 9200)
//Command     : generate_target design_1.bd
//Design      : design_1
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CORE_GENERATION_INFO = "design_1,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=design_1,x_ipVersion=1.00.a,x_ipLanguage=VERILOG,numBlks=3,numReposBlks=3,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,synth_mode=OOC_per_IP}" *) (* HW_HANDOFF = "design_1.hwdef" *) 
module design_1
   (A,
    B,
    C,
    D,
    clk_0);
  input [0:0]A;
  input [0:0]B;
  input [0:0]C;
  output [0:0]D;
  (* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 CLK.CLK_0 CLK" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME CLK.CLK_0, CLK_DOMAIN design_1_clk_0, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, INSERT_VIP 0, PHASE 0.0" *) input clk_0;

  wire [0:0]Op1_0_1;
  wire [0:0]Op2_0_1;
  wire [0:0]Op2_0_2;
  wire clk_0_1;
  wire [0:0]util_vector_logic_0_Res;
  wire [0:0]util_vector_logic_1_Res;

  assign D[0] = util_vector_logic_1_Res;
  assign Op1_0_1 = A[0];
  assign Op2_0_1 = B[0];
  assign Op2_0_2 = C[0];
  assign clk_0_1 = clk_0;
  design_1_ila_0_0 ila_0
       (.clk(clk_0_1),
        .probe0(util_vector_logic_1_Res));
  design_1_util_vector_logic_0_0 util_vector_logic_0
       (.Op1(Op1_0_1),
        .Op2(Op2_0_1),
        .Res(util_vector_logic_0_Res));
  design_1_util_vector_logic_1_0 util_vector_logic_1
       (.Op1(util_vector_logic_0_Res),
        .Op2(Op2_0_2),
        .Res(util_vector_logic_1_Res));
endmodule
