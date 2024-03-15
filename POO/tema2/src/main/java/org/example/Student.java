package org.example;
import java.util.*;

public class Student implements Comparable<Student> {
  protected final String name;
  protected double grade;
  protected final List<String> preferences;
  protected String assignedCourse;

  /* Constructor */
  public Student(String name) {
    this.name = name;
    preferences = new ArrayList<>();
  }

  /* Getters and setters */

  public void setGrade(double grade) {
    this.grade = grade;
  }

  public void setAssignedCourse(String assignedCourse) {
    this.assignedCourse = assignedCourse;
  }

  public List<String> getPreferences() {
    return preferences;
  }

  public double getAverage() {
    return this.grade;
  }

  public String getName() {
    return this.name;
  }

  /* Methods */

  /* Add a preference to the list of preferences */
  public void addPreference(String preference) {
    preferences.add(preference);
  }

  /* Compare students by grade and name */
  public int compareTo(Student student) {
    if (this.grade > student.grade) {
      return -1;
    } else if (this.grade < student.grade) {
      return 1;
    }
    return this.name.compareTo(student.name);
  }

  /* Compare students by name */
  public int compareToAlphabetical(Student student) {
    return this.name.compareTo(student.name);
  }
}
