----------------------------------------------------------------------------------
-- Company: UPB
-- Engineer: Constantinescu Vlad, Popescu Matei
-- 
-- Create Date: 01/09/2024 09:58:06 PM
-- Design Name: 
-- Module Name: vending_machine - Behavioral
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


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity vending_machine is
    Port ( clk : in  STD_LOGIC;
           reset : in  STD_LOGIC;
           inputs : in  STD_LOGIC_VECTOR (7 downto 0);
           -- vector codification
           --   7 = 50 bani
           --   6 = 1 leu
           --   5 = 5 lei
           --   4 = 10 lei
           --   3 = produs1 - 2.5 lei
           --   2 = produs2 - 3 lei
           --   1 = produs3 - 5 lei
           --   0 = change
           product1_selected : out STD_LOGIC;
           product2_selected : out STD_LOGIC;
           product3_selected : out STD_LOGIC;
           change_50bani : out STD_LOGIC;
           change_1leu : out STD_LOGIC;
           insufficient_funds : out STD_LOGIC;
           cash_overflow : out STD_LOGIC );
end vending_machine;

architecture Behavioral of vending_machine is
    type statetype is (parse_input, change);
    signal state, nextstate: statetype;
    -- for ease of use, credit will represent the values as such:
    -- 50 bani = 5, 1 leu = 10, 5 lei = 50, 10 lei = 100
    shared variable credit : natural range 0 to 150 := 0;
    shared variable nr_bills : natural := 0;
    shared variable nr_coins : natural := 0;
    signal bought_product : STD_LOGIC;
begin
-- state register
    process(clk, reset) begin
        if reset = '1' then
            state <= parse_input;
        elsif rising_edge(clk) then
            state <= nextstate;
        end if;
    end process;

-- next state logic
    process(state, inputs, clk) begin
        product1_selected <= '0';
        product2_selected <= '0';
        product3_selected <= '0';
        change_50bani <= '0';
        change_1leu <= '0';
        insufficient_funds <= '0';
        cash_overflow <= '0';
        
        if rising_edge(clk) then
            case state is
                 when parse_input => if credit <= 150 then
                                         if inputs = "10000000" then
                                           credit := credit + 5;
                                           nr_coins := nr_coins + 1;
                                         elsif inputs = "01000000" then
                                           credit := credit + 10;
                                           nr_bills := nr_bills + 1;
                                         elsif inputs = "0010000" then
                                           credit := credit + 50;
                                         elsif inputs = "00010000" then
                                           credit := credit + 100;
                                         end if;
                                     else
                                         cash_overflow <= '1';
                                         credit := credit - (credit - 150);
                                     end if;
                                     if inputs = "00001000" then
                                         if credit >= 25 then
                                             bought_product <= '1';
                                             credit := credit - 25;
                                             product1_selected <= '1';
                                         else
                                             insufficient_funds <= '1';
                                         end if;
                                     end if;
                                     if inputs = "00000100" then
                                         if credit >= 30 then
                                             bought_product <= '1';
                                             credit := credit - 30;
                                             product2_selected <= '1';
                                         else
                                             insufficient_funds <= '1';
                                         end if;
                                     end if;
                                     if inputs = "00000010" then
                                         if credit >= 50 then
                                             bought_product <= '1';
                                             credit := credit - 50;
                                             product3_selected <= '1';
                                         else
                                             insufficient_funds <= '1';
                                         end if;
                                     end if;
                                     if inputs = "00000001" then
                                          nextstate <= change;
                                     end if;
                               
                when change => if credit /= 0 then
                                   if bought_product /= '1' then
                                       credit := credit - 10;
                                   end if;
                                   if credit >= 10 and nr_bills /= 0 then
                                       nr_bills := nr_bills - 1;
                                       credit := credit - 10;
                                       change_1leu <= '1';
                                       nextstate <= change;
                                   elsif nr_coins /= 0 then
                                       nr_coins := nr_coins - 1;
                                       credit := credit - 5;
                                       change_50bani <= '1';
                                       nextstate <= change;
                                   else 
                                       insufficient_funds <= '1';
                                       nextstate <= parse_input;
                                       bought_product <= '0';
                                   end if;
                               else
                                   nextstate <= parse_input;
                                   bought_product <= '0';
                               end if;      
                when others => nextstate <= parse_input;
                               bought_product <= '0';
            end case;
        end if;
    end process;

end Behavioral;
