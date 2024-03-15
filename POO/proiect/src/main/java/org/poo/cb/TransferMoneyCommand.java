package org.poo.cb;

import java.util.HashMap;

public class TransferMoneyCommand implements Command{
  private final String email;
  private final String emailFriend;
  private final String currency;
  private final double amount;
  HashMap<String, User> users;

  public TransferMoneyCommand(String[] args, HashMap<String, User> users) {
    this.email = args[0];
    this.emailFriend = args[1];
    this.currency = args[2];
    this.amount = Double.parseDouble(args[3]);
    this.users = users;
  }

  public void execute() {
    User user = this.users.get(this.email);
    User friend = this.users.get(this.emailFriend);
    if (!(user.getFriends().contains(this.emailFriend))) {
      System.out.println("You are not allowed to trasfer money to " +
              this.emailFriend);
      return;
    }
    Account srcAccount = user.getAccounts().get(this.currency);
    Account destAccount = friend.getAccounts().get(this.currency);
    if (srcAccount.getAmount() < this.amount) {
      System.out.println("Insufficient amount in account " + this.currency +
              " for transfer");
      return;
    }
    srcAccount.withdraw(this.amount);
    destAccount.deposit(this.amount);
  }
}
