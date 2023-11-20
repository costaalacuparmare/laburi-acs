public class Main {
  public static void main(String[] args) {
    Library library = new Library();
    library.readBooks();
    library.printBooks();
    System.out.println();
    library.sortBooks();
    library.printBooks();
    System.out.println();
    Student student = new Student("Matei", 22);
    library.getBookPosition(0).buyBook(student);
    System.out.println(library.getBookPosition(0));
  }
}