----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10/25/2023 02:25:01 PM
-- Design Name: 
-- Module Name: lab2 - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------
library IEEE; use IEEE.STD_LOGIC_1164.all;

entity sillyfunction is
    port (a, b, c: in STD_LOGIC;
          y:       out STD_LOGIC);
end;

architecture synth of sillyfunction is
begin
y <= ((not a) and (not b) and (not c)) or
     (a and (not b) and (not c)) or
     (a and (not b) and c);
end;