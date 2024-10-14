-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
-- Date        : Wed Mar 29 13:07:31 2023
-- Host        : DESKTOP-1FEJ3MB running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/student/laborator_324CB/lab_2/lab3_324CB/lab3_324CB.gen/sources_1/bd/design_2/ip/design_2_numarator_59_0_1_0/design_2_numarator_59_0_1_0_stub.vhdl
-- Design      : design_2_numarator_59_0_1_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_2_numarator_59_0_1_0 is
  Port ( 
    reset : in STD_LOGIC;
    pauza : in STD_LOGIC;
    clk_out_led : in STD_LOGIC;
    valoare_bin : out STD_LOGIC_VECTOR ( 5 downto 0 );
    carry_out : out STD_LOGIC
  );

end design_2_numarator_59_0_1_0;

architecture stub of design_2_numarator_59_0_1_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "reset,pauza,clk_out_led,valoare_bin[5:0],carry_out";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "numarator_59_0,Vivado 2022.1";
begin
end;
