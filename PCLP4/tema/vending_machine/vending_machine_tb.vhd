library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity tb_vending_machine is
end tb_vending_machine;

architecture Behavioral of tb_vending_machine is
    signal clk, reset: STD_LOGIC := '0';
    signal inputs: STD_LOGIC_VECTOR(7 downto 0) := (others => '0');
    signal product1_selected, product2_selected, product3_selected: STD_LOGIC := '0';
    signal change_50bani, change_1leu, insufficient_funds, cash_overflow : STD_LOGIC := '0';
    shared variable change_time : natural range 0 to 30 := 0;
begin
    -- Instantiate the vending machine
    vending_machine_inst: entity work.vending_machine
        port map (
            clk => clk,
            reset => reset,
            inputs => inputs,
            product1_selected => product1_selected,
            product2_selected => product2_selected,
            product3_selected => product3_selected,
            change_50bani => change_50bani,
            change_1leu => change_1leu,
            insufficient_funds => insufficient_funds,
            cash_overflow => cash_overflow
        );

    -- Clock process
    process
    begin
        clk <= '0';
        wait for 5 ns;
        clk <= '1';
        wait for 5 ns;
    end process;

    -- Stimulus process
    process
    begin
        wait for 10 ns;
        reset <= '1';  -- Activate reset
        wait for 10 ns;
        reset <= '0';  -- Deactivate reset
        
         -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;

        -- Simulate selecting product 1
        inputs <= "00001000";  -- Select product 1
        wait for 10 ns;

        -- Simulate inserting 50 bani
        inputs <= "10000000";  -- 50 bani
        change_time := change_time + 1;
        wait for 10 ns;
        
         -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate selecting product 1
        inputs <= "00001000";  -- Select product 1
        wait for 10 ns;

        -- Simulate selecting product 2
        inputs <= "00000100";  -- Select product 2
        wait for 10 ns;
        
        -- Simulate inserting 50 bani
        inputs <= "10000000";  -- 50 bani
        wait for 10 ns;
        
         -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
         -- Simulate selecting product 1
        inputs <= "00001000";  -- Select product 1
        wait for 10 ns;

        -- Simulate pressing change button
        inputs <= "00000001";  -- Change
        change_time := change_time - 1;
        wait for change_time * 10 ns;
        change_time := 0;
        
        -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate inserting 1 leu
        inputs <= "01000000";  -- 1 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate change without product selectiom
        inputs <= "00000001"; -- Change
        wait for change_time * 10 ns;
        change_time := 0;
        
        -- Simulate inserting 5 leu
        inputs <= "00100000";  -- 5 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate inserting 10 leu
        inputs <= "00010000";  -- 10 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Simulate inserting 10 leu
        inputs <= "00010000";  -- 10 leu
        change_time := change_time + 1;
        wait for 10 ns;
        
        -- Finished input
        inputs <= "00000000";
        wait for 10 ns;

        -- Add more test scenarios as needed

        wait;
    end process;

end Behavioral;