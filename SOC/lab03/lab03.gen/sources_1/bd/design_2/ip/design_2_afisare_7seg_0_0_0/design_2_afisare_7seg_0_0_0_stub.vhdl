-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
-- Date        : Wed Mar 29 13:17:21 2023
-- Host        : DESKTOP-1FEJ3MB running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/student/laborator_324CB/lab_2/lab3_324CB/lab3_324CB.gen/sources_1/bd/design_2/ip/design_2_afisare_7seg_0_0_0/design_2_afisare_7seg_0_0_0_stub.vhdl
-- Design      : design_2_afisare_7seg_0_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_2_afisare_7seg_0_0_0 is
  Port ( 
    clk_out_seg : in STD_LOGIC;
    reset : in STD_LOGIC;
    BCD0 : in STD_LOGIC_VECTOR ( 3 downto 0 );
    BCD1 : in STD_LOGIC_VECTOR ( 3 downto 0 );
    BCD2 : in STD_LOGIC_VECTOR ( 3 downto 0 );
    BCD3 : in STD_LOGIC_VECTOR ( 3 downto 0 );
    An : out STD_LOGIC_VECTOR ( 7 downto 0 );
    Seg : out STD_LOGIC_VECTOR ( 6 downto 0 );
    DP : out STD_LOGIC
  );

end design_2_afisare_7seg_0_0_0;

architecture stub of design_2_afisare_7seg_0_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk_out_seg,reset,BCD0[3:0],BCD1[3:0],BCD2[3:0],BCD3[3:0],An[7:0],Seg[6:0],DP";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "afisare_7seg_0,Vivado 2022.1";
begin
end;
