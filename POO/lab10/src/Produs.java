import java.util.ArrayList;

public abstract class Produs implements Comparable{
  abstract double pretRaft();
  abstract void afiseaza();

  @Override
  public int compareTo(Object o) {
    Produs p = (Produs) o;
    if (this.pretRaft() < p.pretRaft()) {
      return -1;
    } else if (this.pretRaft() > p.pretRaft()) {
      return 1;
    } else {
      return 0;
    }
  }
  public static void pretRaftMaxim(ArrayList<? extends Produs> lista) {
    double max = lista.get(0).pretRaft();
    ArrayList<Produs> lista2 = new ArrayList<>();
    for (Produs p : lista) {
      if (p.pretRaft() > max) {
        max = p.pretRaft();
        lista2.add(p);
      }
    }
    lista2.get(lista2.size() - 1).afiseaza();
  }
}
