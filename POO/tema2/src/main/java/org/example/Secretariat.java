package org.example;
import java.util.*;
import java.io.*;

public class Secretariat {
  private final Map<String, Student> studentDatabase;
  private final LinkedHashMap<String, Course<Master>> courseMasterDatabase;
  private final LinkedHashMap<String, Course<Bachelor>> courseBachelorDatabase;

  /* Constructor */
  public Secretariat() {
    studentDatabase = new HashMap<>();
    courseMasterDatabase = new LinkedHashMap<>();
    courseBachelorDatabase = new LinkedHashMap<>();
  }

  /* Student Methods */

  /* Add a student to the database, verifies that student is not duplicate */
  public void addStudent(Student student) throws DuplicateStudentException {
    String name = student.getName();
    if (studentDatabase.containsKey(name)) {
      throw new DuplicateStudentException("***\nStudent duplicat: " + name);
    }
    studentDatabase.put(name, student);
  }

  /* add the admission grade to the student */
  public void addGrade(String name, double grade) {
    Student student = studentDatabase.get(name);
    student.setGrade(grade);
  }

  /* Read the admission grades from a file */
  public void readGrade(String filepath, File file)
          throws FileNotFoundException {
    String gradesInput = Main.readInput(filepath + file.getName());
    String[] rows = gradesInput.split("\n");
    for (String row : rows) {
      String[] gradesInfo = row.split(" - ");
      addGrade(gradesInfo[0], Double.parseDouble(gradesInfo[1]));
    }
  }

  /* Change the admission grade of a student */
  public void changeGrade(String name, double grade) {
    Student student = studentDatabase.get(name);
    student.setGrade(grade);
  }

  /* Post the admission grades sorted by average grade */
  public void postGrade(String outFile) {
    Main.writeOutput(outFile, "***");
    List<Student> students;
    students = new ArrayList<>(studentDatabase.values());
    students.sort(Student :: compareTo);
    for (Student student : students) {
      Main.writeOutput(outFile, student.getName() + " - " +
              student.getAverage());
    }
  }


  /* add a preference to a student */
  public void addPreference(String studentName, String courseName) {
    Student student = studentDatabase.get(studentName);
    student.addPreference(courseName);
  }

  /* Enroll a student in a bachelor course */
  private boolean enrollStudentBachelor(Student student,
                                        Course<Bachelor> course) {
    /* If the course has capacity, add the student to the course */
    if (course.getCapacity() > 0) {
      course.addStudent((Bachelor) student);
      course.setCapacity(course.getCapacity() - 1);
      student.setAssignedCourse(course.getName());
      return true;
    /* If the course has no capacity, but the student has the minimum grade */
    } else if (course.getCapacity() == 0 && student.getAverage() ==
            course.getMinimumGrade()) {
      course.addStudent((Bachelor) student);
      student.setAssignedCourse(course.getName());
      return true;
    }
    return false;
  }

  /* Enroll a student in a master course */
  private boolean enrollStudentMaster(Student student,
                                      Course<Master> course) {
    /* If the course has capacity, add the student to the course */
    if (course.getCapacity() > 0) {
      course.addStudent((Master) student);
      course.setCapacity(course.getCapacity() - 1);
      student.setAssignedCourse(course.getName());
      return true;
    /* If the course has no capacity, but the student has the minimum grade */
    } else if (course.getCapacity() == 0 && student.getAverage() ==
            course.getMinimumGrade()) {
      course.addStudent((Master) student);
      student.setAssignedCourse(course.getName());
      return true;
    }
    return false;
  }

  /* Post a student's info */
  public void postStudent(String outFile, String studentName) {
    Main.writeOutput(outFile, "***");
    Student student = studentDatabase.get(studentName);
    Main.writeOutput(outFile, student.toString());
  }

  /* Course Methods */

  /* add a course to the database, verifies that course is not duplicate */

  /* different methods for master courses because of generics */
  public void addMasterCourse(Course<Master> course)
          throws DuplicateCourseException {
    String name = course.getName();
    if (courseMasterDatabase.containsKey(name) ||
        courseBachelorDatabase.containsKey(name))
      throw new DuplicateCourseException("***\n Curs Duplicat:" + name);
    courseMasterDatabase.put(name, course);
  }

  /* different methods for master courses because of generics */
  public void addBachelorCourse(Course<Bachelor> course)
          throws DuplicateCourseException {
    String name = course.getName();
    if (courseBachelorDatabase.containsKey(name) ||
        courseMasterDatabase.containsKey(name))
      throw new DuplicateCourseException("***\n Curs Duplicat:" + name);
    courseBachelorDatabase.put(name, course);
  }

  /* add a student to a course by student preferences of */
  public void allocateCourses() {
    /* student lists imported from database*/
    List<Student> students;
    students = new ArrayList<>(studentDatabase.values());
    students.sort(Student :: compareTo);

    /* master and bachelor courses imported from database */
    List<Course<Master>> coursesMaster;
    coursesMaster = new ArrayList<>(courseMasterDatabase.values());
    List<Course<Bachelor>> coursesBachelor;
    coursesBachelor = new ArrayList<>(courseBachelorDatabase.values());

    /* assign students to courses by preferences */
    boolean assigned;
    for (Student student : students) {
      assigned = false;
      for (String preference : student.getPreferences()) {
        if (student instanceof Bachelor && !assigned) {
          for (Course<Bachelor> course : coursesBachelor) {
            if (course.getName().equals(preference)) {
              if (enrollStudentBachelor(student, course)) {
                assigned = true;
                break;
              }
            }
          }
        }
        if (student instanceof Master && !assigned) {
          for (Course<Master> course : coursesMaster) {
            if (course.getName().equals(preference)) {
              if (enrollStudentMaster(student, course)) {
                assigned = true;
                break;
              }
            }
          }
        }
      }
    }
    /*
     * if a student is not assigned to a course by preference, assign him to
     * the first course that has capacity or the minimum grade
     */
    for (Student student : students) {
      assigned = false;
      if (student instanceof Bachelor) {
        for (Course<Bachelor> course : coursesBachelor) {
          if (course.getStudents().contains(student)) {
            assigned = true;
            break;
          }
        }
        if (!assigned) {
          for (Course<Bachelor> course : coursesBachelor) {
            if (enrollStudentBachelor(student, course)) break;
          }
        }
      }
      if (student instanceof Master) {
        for (Course<Master> course : coursesMaster) {
          if (course.getStudents().contains(student)) {
            assigned = true;
            break;
          }
        }
        if (!assigned) {
          for (Course<Master> course : coursesMaster) {
            if (enrollStudentMaster(student, course)) break;
          }
        }
      }
    }
  }

  /* Post the courses sorted by name */
  public void postCourse(String outFile, String courseName) {
    Main.writeOutput(outFile, "***");
    if (courseMasterDatabase.containsKey(courseName)) {
      Main.writeOutput(outFile,
                       courseMasterDatabase.get(courseName).toString());
      return;
    }
    if (courseBachelorDatabase.containsKey(courseName)) {
      Main.writeOutput(outFile,
                       courseBachelorDatabase.get(courseName).toString());
    }
  }
}
