package org.example;

/* Exception thrown when a student is added twice to the list of students */
public class DuplicateCourseException extends Exception {
  public DuplicateCourseException(String message) {
    super(message);
  }
}
