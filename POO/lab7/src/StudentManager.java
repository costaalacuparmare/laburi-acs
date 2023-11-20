import java.util.ArrayList;
import java.util.List;

public class StudentManager {

  private IDatabase database;
  private List<Student> students;

  public List<Student> getStudents() {
    return students;
  }

  public StudentManager(IDatabase database) {
    this.students = new ArrayList<>();
    this.database = database;
  }

  public void insertStudent(Student student) {
    this.database.connect();
    this.database.insert(student);
    this.database.disconnect();
  }

  public void updateStudent(Student student, Student newStudent) {
    this.database.connect();
    this.database.update(student, newStudent);
    this.database.disconnect();

  }

  public void deleteStudent(Student student) {
    this.database.connect();
    this.database.delete(student);
    this.database.disconnect();
  }

  @Override
  public String toString() {
    StringBuilder sb = new StringBuilder();
    for (Student student : students)
    {
      sb.append(student + "\t");
    }
    return "StudentManager contains " +
            "students: " + sb.toString();
  }

  public void runSomeTests() {
    Student studentVasile = new Student("Vasile");
    Student studentGigel = new Student("Gigel");
    Student studentFlorina = new Student("Florina");

    this.insertStudent(studentVasile);
    System.out.println(this);
    this.deleteStudent(studentGigel);
    System.out.println(this);
    this.updateStudent(studentVasile, studentFlorina);
    System.out.println(this);
    this.insertStudent(studentVasile);
    System.out.println(this);
    this.deleteStudent(studentFlorina);
    System.out.println(this);
    this.insertStudent(studentGigel);
    System.out.println(this);

  }

}