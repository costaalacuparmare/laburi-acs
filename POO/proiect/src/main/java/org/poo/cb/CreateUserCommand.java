package org.poo.cb;

import java.util.HashMap;

public class CreateUserCommand implements Command {
  private final String email;
  private final String firstName;
  private final String lastName;
  private final String address;
  private final HashMap<String, User> users;

  CreateUserCommand(String[] args, HashMap<String, User> users) {
    this.email = args[0];
    this.firstName = args[1];
    this.lastName = args[2];
    StringBuilder sb = new StringBuilder();
    for(int i = 3; i < args.length; ++i) {
      sb.append(args[i]);
      sb.append(" ");
    }
    sb.deleteCharAt(sb.length() - 1);
    this.address = sb.toString();
    this.users = users;
  }

  public void execute() {
    if (this.users.containsKey(this.email)) {
      System.out.println("User with " + this.email + " already exists");
    } else {
      User user = new User.UserBuilder(this.email)
              .firstName(this.firstName)
              .lastName(this.lastName)
              .address(this.address)
              .build();
      this.users.put(this.email, user);
    }
  }
}
