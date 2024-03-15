package TemaTest;

import java.util.ArrayList;

/*
 * Interface for Followable objects.
 * Followable objects are User objects.
 */
public interface Followable {
  /*
   * Detailed in User class.
   */
  boolean follow(String[] strings , ArrayList<User> users);
  boolean unfollow(String[] strings , ArrayList<User> users);
  void getFollowers(String[] strings, ArrayList<User> users);
  void getFollowing();
}
