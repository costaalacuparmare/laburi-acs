package org.poo.cb;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.HashSet;

public class BankingApp {
  private static BankingApp instance;
  private final HashMap<String, User> users;
  private final List<Command> commands;
  private final HashSet<String> recommendedStocks;

  private BankingApp() {
    this.users =  new HashMap<>();
    this.commands = new ArrayList<>();
    this.recommendedStocks = new HashSet<>();
  }

  public static BankingApp getInstance() {
    if (instance == null) {
      instance = new BankingApp();
    }
    return instance;
  }

  public void addExchangeRates(String exchangeRatesFile) {
    ExchangeRates exchangeRates = ExchangeRates.getInstance();
    try {
      exchangeRates.loadRates(exchangeRatesFile);
    } catch (Exception exception) {
      System.out.println("Error loading exchange rates");
      throw new RuntimeException(exception);
    }
  }

  public void addStockValues(String stockValuesFile) {
    StockValues stockValues = StockValues.getInstance();
    try {
      stockValues.loadStockValues(stockValuesFile);
    } catch (Exception exception) {
      System.out.println("Error loading stock values");
      throw new RuntimeException(exception);
    }
  }

  public void addCommands(List<String> commands) {
    for (String command : commands) {
      String[] parts = command.split(" ", 3);
      if (parts.length < 2) {
        return;
      }
      String commandName = parts[0] + " " + parts[1];
      String commandArgsFull = "";
      if (parts.length > 2) {
        commandArgsFull = parts[2];
      }
      String[] commandArgs = commandArgsFull.split(" ");
      switch (commandName) {
        case "CREATE USER":
          this.commands.add(new CreateUserCommand(commandArgs, this.users));
          break;
        case "ADD FRIEND":
          this.commands.add(new AddFriendCommand(commandArgs, this.users));
          break;
        case "BUY PREMIUM":
          this.commands.add(new BuyPremiumCommand(commandArgs[0], this.users));
          break;
        case "ADD ACCOUNT":
          this.commands.add(new AddAccountCommand(commandArgs, this.users));
          break;
        case "ADD MONEY":
          this.commands.add(new AddMoneyCommand(commandArgs, this.users));
          break;
        case "EXCHANGE MONEY":
          this.commands.add(new ExchangeMoneyCommand(commandArgs, this.users));
          break;
        case "TRANSFER MONEY":
          this.commands.add(new TransferMoneyCommand(commandArgs, this.users));
          break;
        case "BUY STOCKS":
          this.commands.add(new BuyStockCommand(commandArgs, this.users,
                  this.recommendedStocks));
          break;
        case "RECOMMEND STOCKS":
          this.commands.add(new RecommendStocksCommand(this.recommendedStocks));
          break;
        case "LIST USER":
          this.commands.add(new ListUserCommand(commandArgs[0], this.users));
          break;
        case "LIST PORTFOLIO":
          this.commands.add(new ListPortfolioCommand(commandArgs, this.users));
          break;
        default:
          System.out.println("Command not found");
      }
    }

  }

  public void runCommands() {
      for (Command command : this.commands) {
        command.execute();
      }
      cleanup();
  }

  private void cleanup() {
    this.users.clear();
    this.commands.clear();
    this.recommendedStocks.clear();
  }
}
