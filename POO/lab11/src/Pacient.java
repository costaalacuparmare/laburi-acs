public class Pacient implements Comparable<Pacient>{
  public String name;
  public int priority;

  public Pacient(String name, int priority) {
    this.name = name;
    this.priority = priority;
  }
  public String toString() {
    return this.name + " " + this.priority;
  }

  @Override
  public int compareTo(Pacient o) {
    return Integer.compare(this.priority, o.priority);
  }
}
