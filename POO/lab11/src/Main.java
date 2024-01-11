import java.util.*;


public class Main {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    MyMap map = new MyMap();
    System.out.print("Student count: ");
    int n = scanner.nextInt();
    for (int i = 1; i <= n; i++) {
      System.out.print("Student name: ");
      String name = scanner.next();
      System.out.print("Student average: ");
      float avg = scanner.nextFloat();
      Student student = new Student(name, avg);
      map.addStudent(student);
    }
    Map<Integer, ArrayList<Student>> myMap = map.createMap();
    for (Map.Entry<Integer, ArrayList<Student> > entry : myMap.entrySet()) {
      System.out.println(entry.getKey() + " " + entry.getValue());
    }
    System.out.println();
    PriorityQueue<Pacient> priorityQueue = new PriorityQueue<>();
    priorityQueue.add(new Pacient("Pacient1", 3));
    priorityQueue.add(new Pacient("Pacient2", 1));
    priorityQueue.add(new Pacient("Pacient3", 2));
    while (!priorityQueue.isEmpty()) {
      System.out.println(priorityQueue.remove());
    }
  }
}
