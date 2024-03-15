package org.poo.cb;

import java.util.HashMap;

public class AddFriendCommand implements Command {
  private final String email;
  private final String emailFriend;
  private final HashMap<String, User> users;

  AddFriendCommand(String[] args, HashMap<String, User> users) {
    this.email = args[0];
    this.emailFriend = args[1];
    this.users = users;
  }

  private boolean isFriend(String email, String emailFriend) {
    User user = this.users.get(email);
    return user.getFriends().contains(emailFriend);
  }

  private void addFriend(String email, String emailFriend) {
    User user = this.users.get(email);
    user.getFriends().add(emailFriend);
  }

  public void execute() {
    if (!this.users.containsKey(this.email)) {
      System.out.println("User with " + this.email + " doesn't exist");
    } else if (!this.users.containsKey(this.emailFriend)) {
      System.out.println("User with " + this.emailFriend + " doesn't exist");
    } else if ((this.users.get(this.email)).getFriends() != null && this.isFriend(this.email, this.emailFriend)) {
      System.out.println("User with " + this.emailFriend + " is already a friend");
    } else {
      this.addFriend(this.email, this.emailFriend);
      this.addFriend(this.emailFriend, this.email);
    }
  }
}
