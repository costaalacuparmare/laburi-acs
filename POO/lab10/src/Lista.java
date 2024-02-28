import java.util.Arrays;

public class Lista<E> {
  private E[] tablou;
  private int nr;

  public Lista(int dim) {
    if (dim <= 0) {
      throw new IllegalArgumentException("dimensiune negativa sau nula");
    }
    tablou = (E[]) new Object[dim];
    nr = 0;
  }

  public void adauga(E x) {
    if (nr == tablou.length) {
      redimensioneaza();
    }
    tablou[nr++] = x;
  }

  public void redimensioneaza() {
    tablou = Arrays.copyOf(tablou, tablou.length + 1);
  }

  public void afiseaza() {
    for (E i : tablou) {
      System.out.println(i);
    }
  }

  public boolean cauta(E x) {
    for (E i : tablou) {
      if (i != null && i.equals(x)) {
        return true;
      }
    }
    return false;
  }
}