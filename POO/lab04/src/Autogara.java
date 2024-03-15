public class Autogara {
  private MijlocTransport[] mijloace;

  public Autogara(int dimensiune) {
    this.mijloace = new MijlocTransport[dimensiune];
  }

  public void adaugaMijlocTransport(MijlocTransport m) {
    for (int i = 0; i < this.mijloace.length; i++) {
      if (this.mijloace[i] == null) {
        this.mijloace[i] = m;
        return;
      }
    }
  }

  public int profitTotal() {
    int profitTotal = 0;
    for (int i = 0; i < this.mijloace.length; i++) {
      profitTotal += this.mijloace[i].profit();
    }
    return profitTotal;
  }

  public String toString() {
    String s = "";
    for (MijlocTransport m : this.mijloace) {
      if (m != null) {
        s += m + "\n";
      }
    }
    return s;
  }

  public static void main(String[] args) {
    Autogara autogara = new Autogara(4);
    Autobuz a1 = new Autobuz("alb", true, 20, 3, 1);
    Autobuz a2 = new Autobuz("verde", true, 30, 4, 2);
    Microbuz m1 = new Microbuz("albastru", true, 15, 5, 3);
    Microbuz m2 = new Microbuz("gri", true, 10, 6, 2);
    autogara.adaugaMijlocTransport(a1);
    autogara.adaugaMijlocTransport(a2);
    autogara.adaugaMijlocTransport(m1);
    autogara.adaugaMijlocTransport(m2);
    System.out.println(autogara);
    System.out.println(autogara.profitTotal());
  }
}