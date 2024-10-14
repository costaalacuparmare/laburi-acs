-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2022.1 (win64) Build 3526262 Mon Apr 18 15:48:16 MDT 2022
-- Date        : Wed Mar 29 13:07:31 2023
-- Host        : DESKTOP-1FEJ3MB running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/Users/student/laborator_324CB/lab_2/lab3_324CB/lab3_324CB.gen/sources_1/bd/design_2/ip/design_2_numarator_59_0_1_0/design_2_numarator_59_0_1_0_sim_netlist.vhdl
-- Design      : design_2_numarator_59_0_1_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a100tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_2_numarator_59_0_1_0_numarator_59_0 is
  port (
    Q : out STD_LOGIC_VECTOR ( 5 downto 0 );
    carry_out : out STD_LOGIC;
    pauza : in STD_LOGIC;
    clk_out_led : in STD_LOGIC;
    reset : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of design_2_numarator_59_0_1_0_numarator_59_0 : entity is "numarator_59_0";
end design_2_numarator_59_0_1_0_numarator_59_0;

architecture STRUCTURE of design_2_numarator_59_0_1_0_numarator_59_0 is
  signal \^q\ : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal carry_out_i_1_n_0 : STD_LOGIC;
  signal carry_out_i_2_n_0 : STD_LOGIC;
  signal counter : STD_LOGIC_VECTOR ( 5 downto 1 );
  signal \counter[0]_i_1_n_0\ : STD_LOGIC;
  signal \counter[5]_i_1_n_0\ : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of carry_out_i_2 : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \counter[1]_i_1\ : label is "soft_lutpair0";
begin
  Q(5 downto 0) <= \^q\(5 downto 0);
carry_out_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000008000"
    )
        port map (
      I0 => carry_out_i_2_n_0,
      I1 => \^q\(3),
      I2 => \^q\(4),
      I3 => \^q\(5),
      I4 => \^q\(2),
      I5 => pauza,
      O => carry_out_i_1_n_0
    );
carry_out_i_2: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => \^q\(1),
      I1 => \^q\(0),
      O => carry_out_i_2_n_0
    );
carry_out_reg: unisim.vcomponents.FDCE
     port map (
      C => clk_out_led,
      CE => '1',
      CLR => reset,
      D => carry_out_i_1_n_0,
      Q => carry_out
    );
\counter[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^q\(0),
      O => \counter[0]_i_1_n_0\
    );
\counter[1]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \^q\(0),
      I1 => \^q\(1),
      O => counter(1)
    );
\counter[2]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"5F205FA05FA05FA0"
    )
        port map (
      I0 => \^q\(0),
      I1 => \^q\(3),
      I2 => \^q\(1),
      I3 => \^q\(2),
      I4 => \^q\(4),
      I5 => \^q\(5),
      O => counter(2)
    );
\counter[3]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"6C4C6CCC6CCC6CCC"
    )
        port map (
      I0 => \^q\(0),
      I1 => \^q\(3),
      I2 => \^q\(1),
      I3 => \^q\(2),
      I4 => \^q\(4),
      I5 => \^q\(5),
      O => counter(3)
    );
\counter[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7F7F80007FFF8000"
    )
        port map (
      I0 => \^q\(0),
      I1 => \^q\(3),
      I2 => \^q\(1),
      I3 => \^q\(2),
      I4 => \^q\(4),
      I5 => \^q\(5),
      O => counter(4)
    );
\counter[5]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => pauza,
      O => \counter[5]_i_1_n_0\
    );
\counter[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7F7FFFFF80000000"
    )
        port map (
      I0 => \^q\(0),
      I1 => \^q\(3),
      I2 => \^q\(1),
      I3 => \^q\(2),
      I4 => \^q\(4),
      I5 => \^q\(5),
      O => counter(5)
    );
\counter_reg[0]\: unisim.vcomponents.FDCE
    generic map(
      INIT => '0'
    )
        port map (
      C => clk_out_led,
      CE => \counter[5]_i_1_n_0\,
      CLR => reset,
      D => \counter[0]_i_1_n_0\,
      Q => \^q\(0)
    );
\counter_reg[1]\: unisim.vcomponents.FDCE
    generic map(
      INIT => '0'
    )
        port map (
      C => clk_out_led,
      CE => \counter[5]_i_1_n_0\,
      CLR => reset,
      D => counter(1),
      Q => \^q\(1)
    );
\counter_reg[2]\: unisim.vcomponents.FDCE
    generic map(
      INIT => '0'
    )
        port map (
      C => clk_out_led,
      CE => \counter[5]_i_1_n_0\,
      CLR => reset,
      D => counter(2),
      Q => \^q\(2)
    );
\counter_reg[3]\: unisim.vcomponents.FDCE
    generic map(
      INIT => '0'
    )
        port map (
      C => clk_out_led,
      CE => \counter[5]_i_1_n_0\,
      CLR => reset,
      D => counter(3),
      Q => \^q\(3)
    );
\counter_reg[4]\: unisim.vcomponents.FDCE
    generic map(
      INIT => '0'
    )
        port map (
      C => clk_out_led,
      CE => \counter[5]_i_1_n_0\,
      CLR => reset,
      D => counter(4),
      Q => \^q\(4)
    );
\counter_reg[5]\: unisim.vcomponents.FDCE
    generic map(
      INIT => '0'
    )
        port map (
      C => clk_out_led,
      CE => \counter[5]_i_1_n_0\,
      CLR => reset,
      D => counter(5),
      Q => \^q\(5)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity design_2_numarator_59_0_1_0 is
  port (
    reset : in STD_LOGIC;
    pauza : in STD_LOGIC;
    clk_out_led : in STD_LOGIC;
    valoare_bin : out STD_LOGIC_VECTOR ( 5 downto 0 );
    carry_out : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of design_2_numarator_59_0_1_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of design_2_numarator_59_0_1_0 : entity is "design_2_numarator_59_0_1_0,numarator_59_0,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of design_2_numarator_59_0_1_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of design_2_numarator_59_0_1_0 : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of design_2_numarator_59_0_1_0 : entity is "numarator_59_0,Vivado 2022.1";
end design_2_numarator_59_0_1_0;

architecture STRUCTURE of design_2_numarator_59_0_1_0 is
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of reset : signal is "xilinx.com:signal:reset:1.0 reset RST";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of reset : signal is "XIL_INTERFACENAME reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
begin
inst: entity work.design_2_numarator_59_0_1_0_numarator_59_0
     port map (
      Q(5 downto 0) => valoare_bin(5 downto 0),
      carry_out => carry_out,
      clk_out_led => clk_out_led,
      pauza => pauza,
      reset => reset
    );
end STRUCTURE;
