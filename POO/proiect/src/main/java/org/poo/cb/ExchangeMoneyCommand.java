package org.poo.cb;

import java.util.HashMap;

public class ExchangeMoneyCommand implements Command{
  private final String email;
  private final String srcCurrency;
  private final String destCurrency;
  private final double amount;
  HashMap<String, User> users;

  public ExchangeMoneyCommand(String[] args, HashMap<String, User> users) {
    this.email = args[0];
    this.srcCurrency = args[1];
    this.destCurrency = args[2];
    this.amount = Double.parseDouble(args[3]);
    this.users = users;
  }

  public void execute() {
    User user = this.users.get(this.email);
    Account srcAccount = user.getAccounts().get(this.srcCurrency);
    Account destAccount = user.getAccounts().get(this.destCurrency);
    ExchangeRates exchangeRates = ExchangeRates.getInstance();
    double exchangeRate = exchangeRates.getRate(this.destCurrency,
            this.srcCurrency);
    double amountWithRate = this.amount * exchangeRate;
    if (amountWithRate > srcAccount.getAmount() / 2 &&
            !user.getPremium()) {
      amountWithRate += amountWithRate *  0.01;
    }
    if (amountWithRate > srcAccount.getAmount()) {
      System.out.println("Insufficient amount in account " + srcCurrency +
              " for exchange");
    }
    srcAccount.withdraw(amountWithRate);
    destAccount.deposit(this.amount);
  }
}
