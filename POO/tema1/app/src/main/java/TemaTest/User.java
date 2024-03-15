package TemaTest;

import java.util.ArrayList;
import static TemaTest.App.USER_ERROR;
import static TemaTest.App.FOLLOW_ERROR;
import static TemaTest.App.FOLLOW_INVALID;
import static TemaTest.App.UNFOLLOW_ERROR;
import static TemaTest.App.UNFOLLOW_INVALID;
import static TemaTest.App.FOLLOWERS_ERROR;
import static TemaTest.App.FOLLOWERS_INVALID;
import static TemaTest.App.PASS_ERROR;
import static TemaTest.App.PASS_INVALID;

public class User implements Followable{
  public String username;
  private String password;
  private final int id;
  public ArrayList<String> followers;
  private final ArrayList<String> following;
  private int likes;
  private static int userID = 1;

  /* Constructor */
  public User(String username, String password) {
    this.username = username;
    this.password = password;
    this.id = userID++;
    this.followers = new ArrayList<>();
    this.following = new ArrayList<>();
  }

  /* Getters and Setters */

  public int getId() {
    return id;
  }
  public String getPassword() {
    return password;
  }
  public ArrayList<String> getFollowingList() {
    return following;
  }

  /* Used for cleanup */
  public static void setUserID(int userID) {
    User.userID = userID;
  }
  /*
   * Bonus command.
   * Change password.
   * Check that old password is not the same as new one.
   * If yes, print error.
   * If no, change password.
   * Used for "change-password" command.
   */
  public boolean setPassword(String[] string) {
    String password = checkPassword(string, PASS_ERROR);
    if (password == null)
      return false;
    if (password.equals(this.password)) {
      System.out.println(PASS_INVALID);
      return false;
    }
    this.password = password;
    return true;
  }
  /*
   * Calculate and set likes for a user.
   * Check if user is author of a post or comment.
   * If yes, add likes to user's likes.
   * Used for "get-most-likes-users" command.
   */
  public void setLikes(ArrayList<Post> posts,
                       ArrayList<Comment> comments) {
    this.likes = 0;
    for (Post o : posts) {
      if (o.author.username.equals(this.username))
        this.likes += o.likes;
    }
    for (Comment o : comments) {
      if (o.author.username.equals(this.username))
        this.likes += o.likes;
    }
  }

  /* Check Methods */

  /*
   * Check if username is not already taken.
   * If yes, return null.
   * If no, return user.
   * Used for "create-user" command.
   */
  public static User checkDuplicateUser(String username, String password,
                                        ArrayList<User> users) {
    User user = new User(username, password);
    for (User o : users) {
      if (o.username.equals(user.username)) {
        System.out.println(USER_ERROR);
        return null;
      }
    }
    return user;
  }
  /*
   * Check if username is valid.
   * If yes, return user.
   * If no, return null.
   * Used for "-username" parameter.
   */
  public String checkUsername(String[] strings, String error) {
    if (strings.length < 4) {
      System.out.println(error);
      return null;
    }
    String username = strings[3];
    if (username.startsWith("-username")) {
      username = username.substring(11, username.length() - 1);
    } else {
      System.out.println(error);
      return null;
    }
    return username;
  }
  /*
   * Check if password is valid.
   * If yes, return password.
   * If no, return null.
   * Used for "change-password" command.
   */
  public String checkPassword(String[] strings, String error) {
    if (strings.length < 4) {
      System.out.println(error);
      return null;
    }
    String password = strings[3];
    if (password.startsWith("-password")) {
      password = password.substring(11, password.length() - 1);
    } else {
      System.out.println(error);
      return null;
    }
    return password;
  }
  /*
   * Check if user is following another user.
   * If yes, return false.
   * If no, return true.
   * Used for "follow" command.
   */
  public boolean checkFollow(String username) {
    for (String s : following)
      if (s.equals(username)) {
        return false;
      }
    return true;
  }

  /* Followable Methods */

  /* Follow a user.
   * Check if user exists.
   * Check if user is not already following the user.
   * If yes, add user to following list.
   * If no, print error.
   * Return true if user was added.
   * Return false if user was not added.
   * Used for "follow-user-by-username" command.
   */
  public boolean follow(String[] strings, ArrayList<User> users) {
    String username = checkUsername(strings, FOLLOW_ERROR);
    if (username == null)
      return false;
    boolean counter = false;
    for (User o : users) {
      if (o.username.equals(username)) {
        for (String s : following) {
          if (s.equals(username)) {
            System.out.println(FOLLOW_INVALID);
            return false;
          }
        }
        following.add(username);
        o.followers.add(this.username);
        counter = true;
        break;
        }
      }
    if (!counter)
      System.out.println(FOLLOW_INVALID);
    return counter;
  }
  /*
   * Unfollow a user.
   * Check if user exists.
   * Check if user is following another user.
   * If yes, remove user from following list.
   * If no, print error.
   * Return true if user was removed.
   * Return false if user was not removed.
   * Used for "unfollow-user-by-username" command.
   */
  public boolean unfollow(String[] strings, ArrayList<User> users) {
    String username = checkUsername(strings, UNFOLLOW_ERROR);
    if (username == null)
      return false;
    boolean counter = false;
    for (User o : users) {
      if (o.username.equals(username)) {
        for (String s : following) {
          if (s.equals(username)) {
            following.remove(username);
            o.followers.remove(username);
            counter = true;
            break;
          }
        }
      }
    }
    if (!counter)
      System.out.println(UNFOLLOW_INVALID);
    return counter;
  }
  /*
   * Get followers of a user.
   * Check if user exists.
   * If yes, print followers.
   * If no, print error.
   * Used for "get-followers" command.
   */
  public void getFollowers(String[] strings, ArrayList<User> users) {
    String username = checkUsername(strings, FOLLOWERS_ERROR);
    if (username == null)
      return;
    boolean counter = false;
    for (User o : users) {
      if (o.username.equals(username)) {
        counter = true;
        System.out.print("{'status' : 'ok', 'message' : [");
        for (String s : o.followers) {
          System.out.print("'" + s + "'");
          if (!s.equals(followers.get(followers.size() - 1)))
            System.out.print(", ");
        }
        System.out.println("]}");
      }
    }
    if (!counter)
      System.out.println(FOLLOWERS_INVALID);
  }
  /*
   * Get following of a user.
   * Check if user exists.
   * If yes, print following.
   * If no, print error.
   * Used for "get-following" command.
   */
  public void getFollowing() {
    System.out.print("{'status' : 'ok', 'message' : [");
    for (String s : following) {
      System.out.print("'" + s + "'");
      if (!s.equals(following.get(following.size() - 1)))
        System.out.print(", ");
    }
    System.out.println("]}");
  }

  /* toString Methods */

  /* Used for "get-most-followed-users" command. */
  public String toStringFollowers() {
    return "{'username' : '" + this.username + "', 'number_of_followers' : '" +
            this.followers.size() + "' }";
  }
  /* Used for "get-most-liked-users" command. */
  public String toStringLikes() {
    return "{'username' : '" + this.username + "', 'number_of_likes' : '" +
            this.likes + "' }";
  }

  /* compareTo Methods */

  /* Used for "get-most-followed-users" command. */
  public int compareToByFollowers(User o) {
    if (this.followers.size() > o.followers.size())
      return -1;
    else if (this.followers.size() < o.followers.size())
      return 1;
    return 0;
  }
  /* Used for "get-most-liked-users" command. */
  public int compareToByLikes(User o) {
    if (this.likes > o.likes)
      return -1;
    else if (this.likes < o.likes)
      return 1;
    return 0;
  }
}