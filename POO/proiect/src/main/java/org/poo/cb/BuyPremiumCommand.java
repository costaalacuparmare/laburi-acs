package org.poo.cb;

import java.util.HashMap;

public class BuyPremiumCommand implements Command {
  private final String email;
  HashMap<String, User> users;

  public BuyPremiumCommand(String email, HashMap<String, User> users) {
    this.email = email;
    this.users = users;
  }

  public void execute() {
    if (!this.users.containsKey(this.email)) {
      System.out.println("User with " + this.email + " doesn't exist");
      return;
    }
    User user = this.users.get(this.email);
    Account account = user.getAccounts().get("USD");
    if (account.getAmount() < 100) {
      System.out.println("Insufficient amount in account for buying" +
              "premium option");
      return;
    }
    account.withdraw(100);
    user.setPremium(true);
  }
}
