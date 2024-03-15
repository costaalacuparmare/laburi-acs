package org.poo.cb;

import java.util.HashMap;
import java.util.HashSet;

public class BuyStockCommand implements Command {
  private final String email;
  private final String stock;
  private final int numOfStocks;
  HashMap<String, User> users;
  HashSet<String> recommendedStocks;

  public BuyStockCommand(String[] args, HashMap<String, User> users,
                         HashSet<String> recommendedStocks) {
    this.email = args[0];
    this.stock = args[1];
    this.numOfStocks = Integer.parseInt(args[2]);
    this.users = users;
    this.recommendedStocks = recommendedStocks;
  }

  public void execute() {
    User user = this.users.get(this.email);
    HashMap<String, double[]> stockValues =
            StockValues.getInstance().getStockValues();
    double amount = stockValues.get(this.stock)
            [stockValues.get(this.stock).length - 1] * this.numOfStocks;
    if (user.getAccounts().get("USD").getAmount() < amount) {
      System.out.println("Insufficient amount in account for buying stock");
      return;
    }
    if (this.recommendedStocks.contains(this.stock)) {
      amount -= amount * 0.05;
    }
    user.getAccounts().get("USD").withdraw(amount);
    if (user.getStocks().containsKey(this.stock)) {
      user.getStocks().put(this.stock, user.getStocks().get(this.stock) +
              this.numOfStocks);
    } else {
      user.getStocks().put(this.stock, this.numOfStocks);
    }
  }
}
