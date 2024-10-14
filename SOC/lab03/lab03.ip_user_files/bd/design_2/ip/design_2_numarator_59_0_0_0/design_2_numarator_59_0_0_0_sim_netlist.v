// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
// Date        : Wed Mar 29 13:07:31 2023
// Host        : DESKTOP-1FEJ3MB running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim
//               c:/Users/student/laborator_324CB/lab_2/lab3_324CB/lab3_324CB.gen/sources_1/bd/design_2/ip/design_2_numarator_59_0_0_0/design_2_numarator_59_0_0_0_sim_netlist.v
// Design      : design_2_numarator_59_0_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "design_2_numarator_59_0_0_0,numarator_59_0,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "module_ref" *) 
(* X_CORE_INFO = "numarator_59_0,Vivado 2022.1" *) 
(* NotValidForBitStream *)
module design_2_numarator_59_0_0_0
   (reset,
    pauza,
    clk_out_led,
    valoare_bin,
    carry_out);
  (* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 reset RST" *) (* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME reset, POLARITY ACTIVE_LOW, INSERT_VIP 0" *) input reset;
  input pauza;
  input clk_out_led;
  output [5:0]valoare_bin;
  output carry_out;

  wire carry_out;
  wire clk_out_led;
  wire pauza;
  wire reset;
  wire [5:0]valoare_bin;

  design_2_numarator_59_0_0_0_numarator_59_0 inst
       (.Q(valoare_bin),
        .carry_out(carry_out),
        .clk_out_led(clk_out_led),
        .pauza(pauza),
        .reset(reset));
endmodule

(* ORIG_REF_NAME = "numarator_59_0" *) 
module design_2_numarator_59_0_0_0_numarator_59_0
   (Q,
    carry_out,
    pauza,
    clk_out_led,
    reset);
  output [5:0]Q;
  output carry_out;
  input pauza;
  input clk_out_led;
  input reset;

  wire [5:0]Q;
  wire carry_out;
  wire carry_out_i_1_n_0;
  wire carry_out_i_2_n_0;
  wire clk_out_led;
  wire [5:1]counter;
  wire \counter[0]_i_1_n_0 ;
  wire \counter[5]_i_1_n_0 ;
  wire pauza;
  wire reset;

  LUT6 #(
    .INIT(64'h0000000000008000)) 
    carry_out_i_1
       (.I0(carry_out_i_2_n_0),
        .I1(Q[3]),
        .I2(Q[4]),
        .I3(Q[5]),
        .I4(Q[2]),
        .I5(pauza),
        .O(carry_out_i_1_n_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT2 #(
    .INIT(4'h8)) 
    carry_out_i_2
       (.I0(Q[1]),
        .I1(Q[0]),
        .O(carry_out_i_2_n_0));
  FDCE carry_out_reg
       (.C(clk_out_led),
        .CE(1'b1),
        .CLR(reset),
        .D(carry_out_i_1_n_0),
        .Q(carry_out));
  LUT1 #(
    .INIT(2'h1)) 
    \counter[0]_i_1 
       (.I0(Q[0]),
        .O(\counter[0]_i_1_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT2 #(
    .INIT(4'h6)) 
    \counter[1]_i_1 
       (.I0(Q[0]),
        .I1(Q[1]),
        .O(counter[1]));
  LUT6 #(
    .INIT(64'h5F205FA05FA05FA0)) 
    \counter[2]_i_1 
       (.I0(Q[0]),
        .I1(Q[3]),
        .I2(Q[1]),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(Q[5]),
        .O(counter[2]));
  LUT6 #(
    .INIT(64'h6C4C6CCC6CCC6CCC)) 
    \counter[3]_i_1 
       (.I0(Q[0]),
        .I1(Q[3]),
        .I2(Q[1]),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(Q[5]),
        .O(counter[3]));
  LUT6 #(
    .INIT(64'h7F7F80007FFF8000)) 
    \counter[4]_i_1 
       (.I0(Q[0]),
        .I1(Q[3]),
        .I2(Q[1]),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(Q[5]),
        .O(counter[4]));
  LUT1 #(
    .INIT(2'h1)) 
    \counter[5]_i_1 
       (.I0(pauza),
        .O(\counter[5]_i_1_n_0 ));
  LUT6 #(
    .INIT(64'h7F7FFFFF80000000)) 
    \counter[5]_i_2 
       (.I0(Q[0]),
        .I1(Q[3]),
        .I2(Q[1]),
        .I3(Q[2]),
        .I4(Q[4]),
        .I5(Q[5]),
        .O(counter[5]));
  FDCE #(
    .INIT(1'b0)) 
    \counter_reg[0] 
       (.C(clk_out_led),
        .CE(\counter[5]_i_1_n_0 ),
        .CLR(reset),
        .D(\counter[0]_i_1_n_0 ),
        .Q(Q[0]));
  FDCE #(
    .INIT(1'b0)) 
    \counter_reg[1] 
       (.C(clk_out_led),
        .CE(\counter[5]_i_1_n_0 ),
        .CLR(reset),
        .D(counter[1]),
        .Q(Q[1]));
  FDCE #(
    .INIT(1'b0)) 
    \counter_reg[2] 
       (.C(clk_out_led),
        .CE(\counter[5]_i_1_n_0 ),
        .CLR(reset),
        .D(counter[2]),
        .Q(Q[2]));
  FDCE #(
    .INIT(1'b0)) 
    \counter_reg[3] 
       (.C(clk_out_led),
        .CE(\counter[5]_i_1_n_0 ),
        .CLR(reset),
        .D(counter[3]),
        .Q(Q[3]));
  FDCE #(
    .INIT(1'b0)) 
    \counter_reg[4] 
       (.C(clk_out_led),
        .CE(\counter[5]_i_1_n_0 ),
        .CLR(reset),
        .D(counter[4]),
        .Q(Q[4]));
  FDCE #(
    .INIT(1'b0)) 
    \counter_reg[5] 
       (.C(clk_out_led),
        .CE(\counter[5]_i_1_n_0 ),
        .CLR(reset),
        .D(counter[5]),
        .Q(Q[5]));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;
    reg GRESTORE_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
