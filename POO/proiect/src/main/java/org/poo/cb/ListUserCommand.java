package org.poo.cb;

import java.util.HashMap;

public class ListUserCommand implements Command {
  private final String email;
  private final HashMap<String, User> users;

  ListUserCommand(String email, HashMap<String, User> users) {
    this.email = email;
    this.users = users;
  }

  public void execute() {
    if (!this.users.containsKey(this.email)) {
      System.out.println("User with " + this.email + " doesn't exist");
      return;
    }
    System.out.println(this.users.get(this.email).toStringUser());
  }
}
