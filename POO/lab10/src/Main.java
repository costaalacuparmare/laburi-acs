import java.util.ArrayList;

class Main {

  public static void main(String[] args) {
    // Lista<Integer> listaInt2 = new Lista<>(0);

    Lista<Integer> listaInt = new Lista<>(1);
    listaInt.adauga(1);
    listaInt.adauga(2);
    listaInt.adauga(3);
    listaInt.adauga(4);
    listaInt.afiseaza();
    System.out.println();
    System.out.println(listaInt.cauta(2) + "\n");

    Lista<Double> listaDouble = new Lista<>(3);
    listaDouble.adauga(5.7);
    listaDouble.adauga(2.4);
    listaDouble.adauga(3.2);
    listaDouble.adauga(4.0);
    listaDouble.afiseaza();
    System.out.println();
    System.out.println(listaDouble.cauta(2.0) + "\n");

    Lista<String> listaString = new Lista<>(3);
    listaString.adauga("Ana");
    listaString.adauga("Are");
    listaString.adauga("Mere");
    listaString.adauga("Pere");
    listaString.afiseaza();
    System.out.println();
    System.out.println(listaString.cauta("Are") + "\n");

    ProdusAlimentar p1 = new ProdusAlimentar(10);
    ProdusAlimentar p2 = new ProdusAlimentar(20);
    ProdusAlimentar p3 = new ProdusAlimentar(30);
    ProdusAlimentar p4 = new ProdusAlimentar(40);
    ProdusAlimentar p5 = new ProdusAlimentar(50);
    ProdusIgiena p6 = new ProdusIgiena(60);
    ProdusIgiena p7 = new ProdusIgiena(70);
    ProdusIgiena p8 = new ProdusIgiena(80);
    ProdusIgiena p9 = new ProdusIgiena(90);
    ProdusIgiena p10 = new ProdusIgiena(100);
    ProdusCuratenie p11 = new ProdusCuratenie(110);
    ProdusCuratenie p12 = new ProdusCuratenie(120);
    ProdusCuratenie p13 = new ProdusCuratenie(130);
    ProdusCuratenie p14 = new ProdusCuratenie(140);
    ProdusCuratenie p15 = new ProdusCuratenie(150);
    ArrayList<Produs> lista = new ArrayList<>();
    lista.add(p1);
    lista.add(p2);
    lista.add(p3);
    lista.add(p4);
    lista.add(p5);
    lista.add(p6);
    lista.add(p7);
    lista.add(p8);
    lista.add(p9);
    lista.add(p10);
    lista.add(p11);
    lista.add(p12);
    lista.add(p13);
    lista.add(p14);
    lista.add(p15);
    Produs.pretRaftMaxim(lista);
  }
}
