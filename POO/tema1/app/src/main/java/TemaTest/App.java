package TemaTest;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.Objects;

public class App implements Output{
  /* used arraylists to store users, posts and comments */
  static ArrayList<User> users = new ArrayList<>();
  static ArrayList<Post> posts = new ArrayList<>();
  static ArrayList<Comment> comments = new ArrayList<>();

  /* empty constructor */
  public App() {/* compiled code */}

  /* Login Methods */

  /*
   * Check that the username and password provided are valid.
   * If yes, return credents string with credentials.
   * If no, return -1.
   * Used for "login" method.
   */
  public static void checkCredentials(String[] strings, String[] credents,
                                      String error, String error2) {
    if (strings.length < 2) {
      System.out.println(error);
      return;
    }
    String username = strings[1];
    if (username.startsWith("-u ")) {
      username = username.substring(4, username.length() - 1);
    } else {
      System.out.println(error);
      return;
    }
    if (strings.length < 3) {
      System.out.println(error2);
      return;
    }
    String password = strings[2];
    if (password.startsWith("-p ")) {
      password = password.substring(4, password.length() - 1);
    } else {
      System.out.println(error2);
      return;
    }
    credents[0] = username;
    credents[1] = password;
  }

  /*
   * Check that the username and password provided describe an existing user.
   * If yes, return index of user.
   * If no, return -1.
   * Used for "login" method.
   */
  public static int authenticate(String username, String password,
                          ArrayList<User> users) {
    for (User o : users) {
      if (o.username.equals(username) &&
          (o.getPassword().equals(password)))
        return users.indexOf(o);
    }
    return -1;
  }

  /*
   * Check that the username and password provided describe an existing user.
   * Check credentials to be valid.
   * If credentials are not valid, return -2.
   * Call authenticate method to verify if user exists.
   */
  public static int login(String[] strings, String[] credents) {
    checkCredentials(strings, credents, CRED_ERROR, CRED_ERROR);
    if (credents[0] == null || credents[1] == null)
      return -2;
    return authenticate(credents[0], credents[1], users);
  }

  /* Getter Methods */

  /*
   * Check if the provided id is valid.
   * If yes, return id.
   * If no, return -1.
   * Implemented in App because it is used in multiple classes.
   * Used for all id dependent commands.
   */
  public static int getID(String[] strings, String idCheck, int idPos,
                              String error) {
    if (strings.length < 4) {
      System.out.println(error);
      return -1;
    }
    String idArg = strings[3];
    int id;
    if (idArg.startsWith(idCheck)) {
      id = idArg.charAt(idPos) - '0';
    } else {
      System.out.println(error);
      return -1;
    }
    return id;
  }
  /*
   * Check if the provided text is valid.
   * If yes, return text.
   * If no, return null.
   * Implemented in App because it is used in multiple classes.
   * checkText exists in Post and Comment classes because of return type.
   * Used for all text dependent commands.
   */
  public static String getString(String text, String error) {
    if (text.startsWith("-text")) {
      if (text.length() > 305) {
        System.out.println(error);
        return null;
      }
      text = text.substring(7, text.length() - 1);
    } else {
      System.out.println(TEXT_ERROR);
      return null;
    }
    return text;
  }
  /*
   * Return the date of the post or comment with String type.
   * Implemented in App because it is used in multiple classes.
   * Used for all "create-post" & "create-comment" commands.
   */
  public static String getDate() {
    DateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy");
    Date date = new Date();
    return dateFormat.format(date);
  }

  public static void main(java.lang.String[] strings) {
    /* Dummy case */
    if (strings == null) {
      System.out.println("Hello world!");
      return;
    }
    /* credents array used to store username and password */
    String[] credents = new String[2];
    switch (strings[0]) {
      /* User commands */

      /*
        * Check that the username and password provided are valid.
        * If user already exists, print error.
        * If user does not exist, create user.
        * Add user to users arraylist.
       */
      case "-create-user": {
        checkCredentials(strings, credents, USERNAME_ERROR, PASSWORD_ERROR);
        if (credents[0] == null || credents[1] == null)
          break;
        User user = User.checkDuplicateUser(credents[0], credents[1], users);
        if (user == null)
          break;
        users.add(user);
        System.out.println(USER_OK);
        break;
      }
      /*
        * Bonus command
        * Check that the username and password provided are valid.
        * Calls setPassword method from User class.
        * Verifies setPassword method return value.
       */
      case "-change-password": {
        users.add(new User("test", "test"));
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        if(users.get(userIdx).setPassword(strings))
          System.out.println(OPERATION_OK);
        break;
      }
      /*
        * Check that the username and password provided are valid.
        * Calls follow method from User class.
        * Verifies follow method return value.
       */
      case "-follow-user-by-username": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if(users.get(userIdx).follow(strings, users))
          System.out.println(OPERATION_OK);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls unfollow method from User class.
       * Verifies unfollow method return value.
       */
      case "-unfollow-user-by-username": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if(users.get(userIdx).unfollow(strings, users))
          System.out.println(OPERATION_OK);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls getFollowing method from User class.
       */
      case "-get-following": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        users.get(userIdx).getFollowing();
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls getFollowers method from User class.
       */
      case "-get-followers": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        users.get(userIdx).getFollowers(strings, users);
        break;
      }

      /* Post commands */

      /*
       * Check that the username and password provided are valid.
       * Check that the text provided is valid and creates post.
       * Add author to post.
       * Add post to posts arraylist.
       */
      case "-create-post": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        Post post = Post.checkText(strings);
        if (post == null)
          break;
        post.author = users.get(userIdx);
        posts.add(post);
        System.out.println(POST_OK);
        break;
      }
      /*
        * Check that the username and password provided are valid.
        * Calls getID method from App class.
        * Searches for post with id.
        * If post is found, check author to authorize delete.
        * If author is not the same, print error.
        * If author is the same, delete post.
       */
      case "-delete-post-by-id": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        int postID = getID(strings, "-id", 5, ID_ERROR);
        if (postID == -1)
          break;
        /* used counter to verify command validity */
        boolean counter = false;
        for (Post o : posts) {
          if (o.getId() == postID) {
            if (o.author.getId() == users.get(userIdx).getId()) {
              posts.remove(o);
              System.out.println(POST_DELETE);
              counter = true;
            }
            break;
          }
        }
        if (!counter)
          System.out.println(ID_INVALID);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls getID method from App class.
       * Searches for post with id.
       * If post is found, checks if user already likes the post.
       * If user never liked the post, call like from Post class.
       */
      case "-like-post": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        int postID = getID(strings, "-post-id", 10, LIKE_POST_ERROR);
        if (postID == -1)
          break;
        /* used counter to verify command validity */
        boolean counter = false;
        for (Post o : posts) {
          if (o.getId() == postID &&
                  o.checkLikesUsersByID(users.get(userIdx).getId())) {
            o.like(users.get(userIdx).getId());
            System.out.println(OPERATION_OK);
            counter = true;
            break;
          }
        }
        if (!counter)
          System.out.println(LIKE_POST_INVALID);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls getID method from App class.
       * Searches for post with id.
       * If post is found, checks if user likes the post.
       * If user liked the post, call unlike from Post class.
       */
      case "-unlike-post" : {
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        int postID = getID(strings, "-post-id", 10, UNLIKE_POST_ERROR);
        if (postID == -1)
          break;
        /* used counter to verify command validity */
        boolean counter = false;
        for (Post o : posts) {
          if (o.getId() == postID &&
                  !o.checkLikesUsersByID(users.get(userIdx).getId())) {
            o.unlike(users.get(userIdx).getId());
            System.out.println(OPERATION_OK);
            counter = true;
            break;
          }
        }
        if (!counter)
          System.out.println(UNLIKE_POST_INVALID);
        break;
      }

      /* Comment commands */

      /*
       * Check that the username and password provided are valid.
       * Check that the text provided is valid and creates comment.
       * Add author to comment.
       * Add comment to commentsID arraylist from Post class.
       * Add comment to comments arraylist.
       */
      case "-comment-post": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        int postID = getID(strings, "-post-id", 10, TEXT_ERROR);
        if (postID == -1)
          break;
        Comment text = Comment.checkText(strings);
        if (text == null)
          break;
        text.author = users.get(userIdx);
        /* used counter to verify command validity */
        boolean counter = false;
        for (Post o : posts)
          if (o.getId() == postID) {
            counter = true;
            text.post = o;
            o.commentsID.add(text.getId());
            comments.add(text);
            System.out.println(COMMENT_OK);
            break;
          }
        if (!counter)
          System.out.println(ID_INVALID);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls getID method from App class.
       * Searches for comment with id.
       * If comment is found, check author to authorize delete.
       * If author is not the same, print error.
       * If author is the same, delete id from commentID.
       * Delete comment.
       */
      case "-delete-comment-by-id": {
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        int commentID = getID(strings, "-id", 5, ID_ERROR);
        if (commentID == -1)
          break;
        /* used counter to verify command validity */
        boolean counter = false;
        for (Comment o : comments) {
          if (o.getId() == commentID) {
            if (o.author.getId() == users.get(userIdx).getId()) {
              /* remove comment id from post */
              o.post.commentsID.removeIf(i -> i == o.getId());

              comments.remove(o);
              System.out.println(OPERATION_OK);
              counter = true;
            }
            break;
          }
        }
        if (!counter)
          System.out.println(ID_INVALID);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls getID method from App class.
       * Searches for comment with id.
       * If comment is found, checks if user already likes the comment.
       * If user never liked the comment, call like from Comment class.
       */
      case "-like-comment": {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        int commentID = getID(strings, "-comment-id", 13, LIKE_COMMENT_ERROR);
        if (commentID == -1)
          break;
        boolean counter = false;
        for (Comment o : comments) {
          if (o.getId() == commentID &&
                  o.checkLikesUsersByID(users.get(userIdx).getId())) {
            o.like(users.get(userIdx).getId());
            System.out.println(OPERATION_OK);
            counter = true;
            break;
          }
        }
        if (!counter)
          System.out.println(LIKE_COMMENT_INVALID);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Calls getID method from App class.
       * Searches for comment with id.
       * If comment is found, checks if user likes the comment.
       * If user liked the comment, call unlike from Comment class.
       */
      case "-unlike-comment": {
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        int commentID = getID(strings, "-comment-id", 13,
                              UNLIKE_COMMENT_ERROR);
        if (commentID == -1)
          break;
        boolean counter = false;
        for (Comment o : comments) {
          if (o.getId() == commentID &&
                  !o.checkLikesUsersByID(users.get(userIdx).getId())) {
            o.unlike(users.get(userIdx).getId());
            System.out.println(OPERATION_OK);
            counter = true;
            break;
          }
        }
        if (!counter)
          System.out.println(UNLIKE_COMMENT_INVALID);
        break;
      }

      /* Get commands */

      /*
       * Check that the username and password provided are valid.
       * Sort users by number of followers in descending order.
       * Print the first 5 users, if there are less than 5 users, print all.
       * Prints toStringFollowers method from User class.
       */
      case "-get-most-followed-users" : {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        users.sort(User::compareToByFollowers);
        System.out.print("{'status' : 'ok', 'message' : [");
        for (int idx = 0; idx < Math.min(5,users.size()); idx++) {
          System.out.print(users.get(idx).toStringFollowers());
          if (idx != Math.min(5,users.size()) - 1)
            System.out.print(",");
        }
        System.out.println(" ]}");
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Sort users by number of likes in descending order.
       * Print the first 5 users, if there are less than 5 users, print all.
       * Prints toStringLikes method from User class.
       */
      case "-get-most-liked-users" : {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        for (User o : users)
          o.setLikes(posts, comments);
        users.sort(User::compareToByLikes);
        System.out.print("{'status' : 'ok', 'message' : [");
        for (int idx = 0; idx < Math.min(5,users.size()); idx++) {
          System.out.print(users.get(idx).toStringLikes());
          if (idx != Math.min(5,users.size()) - 1)
            System.out.print(",");
        }
        System.out.println("]}");
        break;
      }

      /*
        * Check that the username and password provided are valid.
        * Calls getID method from App class.
        * Prints toStringDetails method from Post class.
       */
      case "-get-post-details" : {
        int userIdx = login(strings, credents);
        if (userIdx == -2)
          break;
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        int postID = getID(strings, "-post-id", 10, POST_ID_ERROR);
        if (postID == -1)
          break;
        /* used counter to verify command validity */
        boolean counter = false;
        for (Post o : posts) {
          if (o.getId() == postID) {
            counter = true;
            comments.sort(Comment::compareToByID);
            System.out.print("{'status' : 'ok', 'message' : [");
            System.out.print(o.toStringDetails(comments));
            System.out.println("] }");
            break;
          }
        }
        if (!counter)
          System.out.println(POST_ID_INVALID);
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Sort posts by number of likes in descending order.
       * Print the first 5 posts, if there are less than 5 posts, print all.
       * Prints toStringLikes method from Post class.
       */
      case "-get-most-liked-posts": {
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        posts.sort(Post::compareToByLikes);
        System.out.print("{'status' : 'ok', 'message' : [");
        for (int idx = 0; idx < Math.min(5,posts.size()); idx++) {
          System.out.print(posts.get(idx).toStringLikes());
          if (idx != Math.min(5,posts.size()) - 1)
            System.out.print(",");
        }
        System.out.println(" ]}");
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Sort posts by number of comments in descending order.
       * Print the first 5 posts, if there are less than 5 posts, print all.
       * Prints toStringCommented method from Post class.
       */
      case "-get-most-commented-posts": {
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        posts.sort(Post::compareToByComments);
        System.out.print("{'status' : 'ok', 'message' : [");
        for (int idx = 0; idx < Math.min(5,posts.size()); idx++) {
          System.out.print(posts.get(idx).toStringCommented());
          if (idx != Math.min(5,posts.size()) - 1)
            System.out.print(",");
        }
        System.out.println("]}");
        break;
      }
      /*
        * Check that the username and password provided are valid.
        * Calls checkUsername method from User class through authenticated user.
        * Calls checkFollow method from User class through authenticated user.
        * If user is followed, creates Post array with all posts from user.
        * Sorts posts by date/id.
        * Prints toStringFollow method from Post class.
       */
      case "-get-user-posts": {
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        String username = users.get(userIdx).checkUsername(strings, LIST_ERROR);
        if (username == null)
          break;
        if(users.get(userIdx).checkFollow(username)) {
          System.out.println(LIST_INVALID);
          break;
        }
        System.out.print("{'status' : 'ok', 'message' : [");
        Post[] followingPosts = new Post[posts.size()];
        int idx = 0;
        for (Post o : posts)
          if (Objects.equals(o.author.username, username))
            followingPosts[idx++] = o;
        Arrays.sort(followingPosts, 0, idx, Post::compareToByID);
        for (int i = 0; i < idx; i++) {
          System.out.print(followingPosts[i].toStringFollow());
          if (i != idx - 1)
            System.out.print(",");
        }
        System.out.println("]}");
        break;
      }
      /*
       * Check that the username and password provided are valid.
       * Creates String arraylist with all users that are followed.
       * Creates Post array with all posts from users that are followed.
       * Sorts posts by date/id.
       * Prints toStringUser method from Post class.
       */
      case "-get-followings-posts": {
        int userIdx = login(strings, credents);
        if (userIdx == -1) {
          System.out.println(LOGIN_ERROR);
          break;
        }
        if (userIdx == -2)
          break;
        ArrayList<String> following = users.get(userIdx).getFollowingList();
        Post[] followingPosts = new Post[posts.size()];
        int idx = 0;
        for (Post o : posts) {
          if (following.contains(o.author.username)) {
            followingPosts[idx++] = o;
          }
        }
        Arrays.sort(followingPosts, 0, idx, Post::compareToByID);
        System.out.print("{'status' : 'ok', 'message' : [");
        for (int i = 0; i < idx; i++) {
          System.out.print(followingPosts[i].toStringUser());
          if (i != idx - 1)
            System.out.print(",");
        }
        System.out.println("]}");
        break;
      }
      /*
       * Deletes all users, posts and comments.
       * Resets user, post and comment id.
       */
      case "-cleanup-all": {
        posts.clear();
        users.clear();
        comments.clear();
        User.setUserID(1);
        Post.setPostID(1);
        Comment.setCommentID(1);
        System.out.println(CLEANUP_OK);
        break;
      }
    }
  }
}