public class Student {
  public String name;
  public float avg;

  public Student (String name, float avg) {
    this.name = name;
    this.avg = avg;
  }
  public float getAvg () {
    return this.avg;
  }
  public String toString () {
    return this.name + " " + this.avg;
  }

}
