package org.example;

import java.util.ArrayList;
import java.util.List;

public class Course<T extends Student> {
  private final String name;
  private int capacity;
  private final int maxCapacity;
  private final List<T> students;

  /* Constructor */
  public Course(String name, int capacity) {
    this.name = name;
    this.capacity = capacity;
    this.maxCapacity = capacity;
    students = new ArrayList<>();
  }

  /* Getters and Setters */

  public void setCapacity(int capacity) {
    this.capacity = capacity;
  }
  public String getName() {
    return this.name;
  }
  public int getCapacity() {
    return this.capacity;
  }
  public List<T> getStudents() {
    return students;
  }

  /* Methods */

  /* Add a student to the list of students */
  public void addStudent(T student) {
      students.add(student);
  }

  /* Get the minimum grade of the students in the course */
  public double getMinimumGrade() {
    double minimumGrade = 10;
    for (T student : students) {
      if (student.getAverage() < minimumGrade) {
        minimumGrade = student.getAverage();
      }
    }
    return minimumGrade;
  }

  /* Print the course with the students sorted alphabetical */
  public String toString() {
    StringBuilder stringCourse = new StringBuilder(this.name + " " +
                                                   "(" + this.maxCapacity + ")"
                                                   + "\n");
    students.sort(Student :: compareToAlphabetical);
    for (T student : students) {
      stringCourse.append(student.getName());
      stringCourse.append(" - ").append(student.getAverage());
      if (students.indexOf(student) != students.size() - 1) {
        stringCourse.append("\n");
      }
    }
    return stringCourse.toString();
  }
}
