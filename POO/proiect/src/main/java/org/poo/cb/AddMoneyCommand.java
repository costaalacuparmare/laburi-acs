package org.poo.cb;

import java.util.HashMap;

public class AddMoneyCommand implements Command {
  private final String email;
  private final String currency;
  private final double amount;
  HashMap<String, User> users;

  public AddMoneyCommand(String[] args, HashMap<String, User> users) {
    this.email = args[0];
    this.currency = args[1];
    this.amount = Double.parseDouble(args[2]);
    this.users = users;
  }

  public void execute() {
    User user = this.users.get(this.email);
    Account account = user.getAccounts().get(this.currency);
    account.deposit(this.amount);
  }
}
