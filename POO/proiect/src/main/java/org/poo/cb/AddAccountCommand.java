package org.poo.cb;

import java.util.HashMap;

public class AddAccountCommand implements Command{
  private final String email;
  private final String currency;
  private final HashMap<String, User> users;

  public AddAccountCommand(String[] args, HashMap<String, User> users) {
    this.email = args[0];
    this.currency = args[1];
    this.users = users;
  }

  public void execute() {
    User user = this.users.get(this.email);
    AccountFactory accountFactory = AccountFactory.getInstance();
    Account account = accountFactory.createAccount(this.currency);
    if (user.getAccounts() != null &&
            user.getAccounts().containsKey(this.currency)) {
      System.out.println("Account in currency " + this.currency +
                         " already exists for user");
    } else {
      user.getAccounts().put(this.currency, account);
    }
  }
}
