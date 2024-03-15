package org.example;

/* Exception thrown when a student is added twice to the list of students */
public class DuplicateStudentException extends Exception {
  public DuplicateStudentException(String message) {
    super(message);
  }
}
