package org.poo.cb;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main implements Constants{
    public static List<String> readCommands(String filename) {
        List<String> commands = new ArrayList<>();
        try {
            File file = new File(filename);
            Scanner scanner = new Scanner(file);
            StringBuilder sb = new StringBuilder();
            while (scanner.hasNextLine()) {
                sb.append(scanner.nextLine());
                commands.add(sb.toString());
                sb.setLength(0);
            }
            return commands;
        } catch (IOException exception) {
            System.out.println("Error reading commands");
            throw new RuntimeException(exception);
        }
    }

    public static void main(String[] args) {
        if (args == null) {
            System.out.println("Running Main");
        } else {
            /* Use singleton pattern to create an instance of BankingApp */
            BankingApp app = BankingApp.getInstance();

            /* Add exchange rates and commands */
            String exchangeRatesFile = FILEPATH + args[0];
            app.addExchangeRates(exchangeRatesFile);

            /* Add stock values */
            String stockValuesFile = FILEPATH + args[1];
            app.addStockValues(stockValuesFile);

            /*
             * Add commands to app who acts as an
             * invoker using command pattern
             */
            String commandsFile = FILEPATH + args[2];
            app.addCommands(readCommands(commandsFile));
            app.runCommands();
        }
    }
}
