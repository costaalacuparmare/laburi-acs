package org.example;

/* Used to differentiate between bachelor and master students */
public class Bachelor extends Student{
  public Bachelor(String name) {
    super(name);
  }

  /* Prints the student's name, grade and assigned course */
  public String toString() {
    String stringStudent;
    stringStudent = "Student Licenta: ";
    stringStudent += this.name + " - " + this.grade
            + " - " + this.assignedCourse;
    return stringStudent;
  }

}
