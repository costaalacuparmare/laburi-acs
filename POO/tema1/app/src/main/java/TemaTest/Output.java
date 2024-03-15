package TemaTest;

/*
 * Interface for Output messages.
 * Implemented in App class and used in all other classes.
 */
public interface Output {
  String USERNAME_ERROR = "{ 'status' : 'error', 'message' : " +
          "'Please provide username'}";
  String PASSWORD_ERROR = "{ 'status' : 'error', 'message' : " +
          "'Please provide password'}";
  String USER_ERROR = "{ 'status' : 'error', 'message' : " +
          "'User already exists'}";
  String PASS_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No password to change with was provided'}";
  String PASS_INVALID = "{ 'status' : 'error', 'message' : " +
          "The password to change with was invalid'}";
  String USER_OK = "{ 'status' : 'ok', 'message' : " +
          "'User created successfully'}";
  String LOGIN_ERROR = "{ 'status' : 'error', 'message' : " +
          "'Login failed'}";
  String CRED_ERROR = "{ 'status' : 'error', 'message' : " +
          "'You need to be authenticated'}";
  String TEXT_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No text provided'}";
  String P_SIZE_ERROR = "{ 'status' : 'error', 'message' : " +
          "'Post text length exceeded'}";
  String POST_OK = "{ 'status' : 'ok', 'message' : " +
          "'Post added successfully'}";
  String POST_ID_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No post identifier was provided'}";
  String POST_ID_INVALID = "{ 'status' : 'error', 'message' : " +
          "'The post identifier was not valid'}";
  String ID_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No identifier was provided'}";
  String ID_INVALID = "{ 'status' : 'error', 'message' : " +
          "'The identifier was not valid'}";
  String POST_DELETE = "{ 'status' : 'ok', 'message' : " +
          "'Post deleted successfully'}";
  String LIST_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No username to list posts was provided'}";
  String LIST_INVALID = "{ 'status' : 'error', 'message' : " +
          "'The username to list posts was not valid'}";
  String FOLLOW_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No username to follow was provided'}";
  String FOLLOW_INVALID = "{ 'status' : 'error', 'message' : " +
          "'The username to follow was not valid'}";
  String UNFOLLOW_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No username to unfollow was provided'}";
  String UNFOLLOW_INVALID = "{ 'status' : 'error', 'message' : " +
          "'The username to unfollow was not valid'}";
  String OPERATION_OK = "{ 'status' : 'ok', 'message' : " +
          "'Operation executed successfully'}";
  String FOLLOWERS_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No username to list followers was provided'}";
  String FOLLOWERS_INVALID = "{ 'status' : 'error', 'message' : " +
          "'The username to list followers was not valid'}";
  String LIKE_POST_ERROR = "{ 'status' : 'error', 'message' : " +
          "'No post identifier to like was provided'}";
  String LIKE_POST_INVALID = "{ 'status' : 'error', 'message' : " +
          "'The post identifier to like was not valid'}";
  String UNLIKE_POST_ERROR = "{ 'status' : 'error', 'message' :" +
          " 'No post identifier to unlike was provided'}";
  String UNLIKE_POST_INVALID = "{ 'status' : 'error', 'message'" +
          " : 'The post identifier to unlike was not valid'}";
  String C_SIZE_ERROR = "{ 'status' : 'error', 'message' : " +
          "'Comment text length exceeded'}";
  String COMMENT_OK = "{ 'status' : 'ok', 'message' : " +
          "'Comment added successfully'}";
  String LIKE_COMMENT_ERROR = "{ 'status' : 'error', 'message' " +
          ": 'No comment identifier to like was provided'}";
  String LIKE_COMMENT_INVALID = "{ 'status' : 'error', 'message'" +
          " : 'The comment identifier to like was not valid'}";
  String UNLIKE_COMMENT_ERROR = "{ 'status' : 'error', 'message'" +
          " : 'No comment identifier to unlike was provided'}";
  String UNLIKE_COMMENT_INVALID = "{ 'status' : 'error', 'message'" +
          " : 'The comment identifier to unlike was not valid'}";
  String CLEANUP_OK = "{ 'status' : 'ok', 'message' : " +
                      "'Cleanup finished successfully'}";
}
