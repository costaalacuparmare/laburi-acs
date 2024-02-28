public class Lista {
  private Nod varf;
  private Nod coada;
  private int contor;
  class Nod {
    private int val;
    private Nod urm;

    public Nod(int x) {
      this.val = x;
      this.urm = null;
    }
    public Nod() {
    }
  }

  static class ContorListe {
    static int numarListe;

    public void incrementNumarListe() {
      ContorListe.numarListe++;
    }
  }
  public Lista() {
    this.varf = null;
    this.coada = null;
    this.contor = 0;
    new ContorListe().incrementNumarListe();
  }
  public void adauga(int x) {
    Nod nod = new Nod(x);
    if (this.varf == null) {
      this.varf = nod;
      this.coada = nod;
    } else {
      this.coada.urm = nod;
      this.coada = nod;
    }
    this.contor++;
  }
  public int dimensiune() {
    return this.contor;
  }
  public void afisareLista() {
    Nod nod = this.varf;
    System.out.printf("[");
    while (nod != null) {
      System.out.print(nod.val);
      if (nod.urm != null)
        System.out.print(", ");
      nod = nod.urm;
    }
    System.out.println("]");
    System.out.println("Numarul de liste este: " + ContorListe.numarListe);
  }
}