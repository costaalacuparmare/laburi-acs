import java.io.IOException;

public class Main {
  public static void main(String[] args) throws IOException {
      ParcAuto p = new ParcAuto("date.txt");
      Auto a = new Auto("Audi", 2010, 0, 10000);
      Auto b = new Auto("BMW", 2010, 10, 10000);
      Auto c = new Auto("Mercedes", 2010, 100, 10000);
      Auto d = new Auto("VW", 2010, 0, 10000);
      p.adaugaAuto(a);
      p.adaugaAuto(b);
      p.adaugaAuto(c);
      p.adaugaAuto(d);
      System.out.println(p);
      System.out.println("Numar masini noi: " + p.NumaraMasiniNoi());
      if (p.cauta(a))
        System.out.println("Masina exista in parc");
      else
        System.out.println("Masina nu exista in parc");
      if (p.verificaFisierBinar()) {
        System.out.println("Fisierul este binar");
      } else {
        System.out.println("Fisierul nu este binar");
      }
    }
}
