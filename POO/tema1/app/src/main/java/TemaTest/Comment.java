package TemaTest;

import java.util.ArrayList;

import static TemaTest.App.getString;
import static TemaTest.App.TEXT_ERROR;
import static TemaTest.App.C_SIZE_ERROR;

public class Comment implements Likeable {
  public String text;
  public User author;
  public Post post;
  public int likes;
  private final ArrayList<Integer> likesUsersByID;
  private final int id;
  public final String date;
  private static int commentID = 1;

  /* Constructor */
  public Comment(String text, User author, Post post) {
    this.text = text;
    this.author = author;
    this.post = post;
    this.id = commentID++;
    this.likesUsersByID = new ArrayList<>();
    this.date = App.getDate();
  }

  /* Getters and Setters */

  public int getId() {
    return id;
  }

  /* Used for cleanup */
  public static void setCommentID(int commentID) {
    Comment.commentID = commentID;
  }

  /* Check Methods */

  /*
   * Check that text is not null.
   * If yes, print error.
   * If no, return text.
   * Similar to checkText method in Post.
   * Used for "create-comment" command.
   */
  public static Comment checkText(String[] strings) {
    if (strings.length < 5) {
      System.out.println(TEXT_ERROR);
      return null;
    }
    String text = strings[4];
    /* getString method detailed in App */
    text = getString(text, C_SIZE_ERROR);
    if (text == null)
      return null;
    return new Comment(text, null, null);
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
   * Add like to comment.
   * Add user id to likesUsersByID.
   * Used for "like-comment" command.
   */
  public void like(int id) {
    this.likes++;
    this.likesUsersByID.add(id);
  }
  /*
   * Remove like from comment.
   * Remove user id from likesUsersByID.
   * Used for "unlike-comment" command.
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

  /*
   * Prints comment details.
   * Used for "get-post-details" command.
   * Called from Post.toStringDetails.
   */
  public String toStringUser() {
    return "{'comment_id' : '" + this.id + "', 'comment_text' : '" +
            this.text + "', 'comment_date' : '" + this.date +
            "', 'username' : '" + this.author.username +
            "', 'number_of_likes' : '" + this.likes + "'}";
  }

  /* compareTo Methods */

  /*
   * Compare comments by likes.
   * Used for "get-post-details" command.
   */
  public int compareToByID(Comment o) {
    if (this.id > o.id)
      return -1;
    else if (this.id < o.id)
      return 1;
    return 0;
  }
}