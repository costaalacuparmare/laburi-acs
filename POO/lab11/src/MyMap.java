import java.util.*;
public class MyMap {
  public ArrayList<Student>[] list = new ArrayList[11];
  public void addStudent (Student s) {
    int avgIndex = (int) Math.round(s.getAvg());
    if (list[avgIndex] == null)
      list[avgIndex] = new ArrayList<Student>();
    list[avgIndex].add(s);
  }
  public Map<Integer,ArrayList<Student>> createMap() {
    Map<Integer,ArrayList<Student>> map = new TreeMap<Integer,
            ArrayList<Student>>(new Comparator<Integer>(){
      public int compare(Integer o1, Integer o2) {
        return o2.compareTo(o1);
      }
    });
    for (int i = 0; i <= 10; i++)
      map.put(i, list[i]);
    return map;
  }
}
