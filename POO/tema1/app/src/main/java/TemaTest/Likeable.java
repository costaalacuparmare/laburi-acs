package TemaTest;

/*
 * Interface for like function methods.
 * Implemented in Post and Comment classes.
 */
public interface Likeable {
  /*
   * Detailed in Post and Comment classes.
   */
  void like(int id);
  void unlike(int id);
  boolean checkLikesUsersByID(int id);
}
