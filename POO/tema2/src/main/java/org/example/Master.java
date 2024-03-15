package org.example;

/* Used to differentiate between bachelor and master students */
public class Master extends Student {
  public Master(String name) {
    super(name);
  }

  /* Prints the student's name, grade and assigned course */
  public String toString() {
    String stringStudent;
    stringStudent = "Student Master: ";
    stringStudent += this.name + " - " + this.grade
            + " - " + this.assignedCourse;
    return stringStudent;
  }
}
