package TemaTest;

import java.util.ArrayList;
import static TemaTest.App.getString;
import static TemaTest.App.P_SIZE_ERROR;
import static TemaTest.App.TEXT_ERROR;

public class Post implements Likeable {
  public String text;
  public User author;
  private final int id;
  public int likes;
  private final ArrayList<Integer> likesUsersByID;
  public ArrayList<Integer> commentsID;
  public String date;
  private static int postID = 1;

  /* Constructor */
  public Post(String text, User author) {
    this.text = text;
    this.author = author;
    this.id = postID++;
    this.likes = 0;
    this.likesUsersByID = new ArrayList<>();
    this.commentsID = new ArrayList<>();
    this.date = App.getDate();
  }

  /* Getters and Setters */

  public int getId() {
    return id;
  }


  /* Used for cleanup */
  public static void setPostID(int postID) {
    Post.postID = postID;
  }

  /* Check Methods */

  /*
   * Check that text is not null.
   * If yes, print error.
   * If no, return text.
   * Used for "create-post" command.
   */
  public static Post checkText(String[] strings) {
    if (strings.length < 4) {
      System.out.println(TEXT_ERROR);
      return null;
    }
    String text = strings[3];

    /* getString method detailed in App */
    text = getString(text, P_SIZE_ERROR);

    if (text == null) return null;
    return new Post(text, null);
  }
  /*
   * Check that user already liked a post.
   * Compare user id with all ids in likesUsersByID.
   * If yes, print error.
   * If no, return user.
   * Used for Likeable methods.
   */
  public boolean checkLikesUsersByID(int id) {
    for (Integer o : likesUsersByID) {
      if (o == id)
        return false;
    }
    return true;
  }

  /* Likeable Methods */

  /*
   * Add like to post.
   * Add user id to likesUsersByID.
   * Used for "like-post" command.
   */
  public void like(int id) {
    this.likes++;
    this.likesUsersByID.add(id);
  }
  /*
   * Remove like from post.
   * Remove user id from likesUsersByID.
   * Used for "unlike-post" command.
   */
  public void unlike(int id) {
    this.likes--;
    for (Integer o : likesUsersByID) {
      if (o == id) {
        this.likesUsersByID.remove(o);
        break;
      }
    }
  }

  /* toString Methods */

  /* Used for "get-following-posts" command. */
  public String toStringUser() {
    return "{'post_id' : '" + this.id + "', 'post_text' : '" + this.text +
           "', 'post_date' : '" + this.date + "', 'username' : '" +
            this.author.username + "'}";
  }
  /* Used for "get-user-posts" command. */
  public String toStringFollow() {
    return "{'post_id' : '" + this.id + "', 'post_text' : '" + this.text +
            "', 'post_date' : '" + this.date + "'}";
  }
  /* Used for "get-most-liked-posts" command. */
  public String toStringLikes() {
    return "{'post_id' : '" + this.id + "', 'post_text' : '" + this.text +
            "', 'post_date' : '" + this.date + "', 'username' : '" +
            this.author.username + "', 'number_of_likes' : '" + this.likes +
            "' }";
  }
  /* Used for "get-most-commented-posts" command. */
  public String toStringCommented() {
    return "{'post_id' : '" + this.id + "', 'post_text' : '" + this.text +
            "', 'post_date' : '" + this.date + "', 'username' : '" +
            this.author.username + "', 'number_of_comments' : '" +
            this.commentsID.size() + "' }";
  }
  /* Used for "get-post-details" command. */
  public String toStringDetails(ArrayList<Comment> comments) {
    /* Used StringBuilder to avoid concatenation */
    StringBuilder prefix;
    prefix = new StringBuilder("{'post_text' : '" + this.text +
                               "', 'post_date' : '" + this.date +
                               "', 'username' : '" + this.author.username +
                               "', 'number_of_likes' : '" + this.likes +
                               "', 'comments' : [");
    for (Comment o : comments) {
      /* toStringUser method detailed in Comment */
      prefix.append(o.toStringUser());
      if (o != comments.get(comments.size() - 1))
        prefix.append(", ");
    }
    prefix.append("] }");
    return prefix.toString();
  }

  /* compareTo Methods */

  /*
   * Used for "get-user-posts" & "get-following-posts" command.
   * Sort by date.
   * If date is equal, better to sort by id.
   */
  public int compareToByID(Post o) {
    if (this.id > o.id)
      return -1;
    else if (this.id < o.id)
      return 1;
    return 0;
  }
  /* Used for "get-most-liked-posts" command. */
  public int compareToByLikes(Post o) {
    if (this.likes > o.likes)
      return -1;
    else if (this.likes < o.likes)
      return 1;
    return 0;
  }
  /* Used for "get-most-commented-posts" command. */
  public int compareToByComments(Post o) {
    if (this.commentsID.size() > o.commentsID.size())
      return -1;
    else if (this.commentsID.size() < o.commentsID.size())
      return 1;
    return 0;
  }
}