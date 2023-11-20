public class Main {
  public static void main(String[] args) {
    Lista lista = new Lista();
    lista.adauga(1);
    lista.adauga(2);
    lista.adauga(3);
    lista.adauga(4);
    lista.adauga(5);
    lista.afisareLista();
    System.out.println("Dimensiunea listei este: " + lista.dimensiune());

    Lista lista2 = new Lista();
    lista2.adauga(2);
    lista2.afisareLista();
    System.out.println("Dimensiunea listei este: " + lista2.dimensiune());
    System.out.println();
    Book book1 = new Book("Eminescu");
    System.out.println(book1);
    Book book2 = new Book("Cosbuc");
    System.out.println(book2);
    Book book3 = new Book("Alecsandri");
    System.out.println(book3);

  }
}
