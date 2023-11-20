import java.util.ArrayList;
import java.util.Scanner;
import java.util.Collections;

public class Library {
  private ArrayList<Book> books = new ArrayList<Book>();

  public void readBooks() {
    System.out.println("Pleaste type information about books:");
    Scanner scanner = new Scanner(System.in);
    while (true) {
      String title = scanner.nextLine();
      if (title.equals("exit")){
        break;
      }
      String author = scanner.nextLine();
      int year = scanner.nextInt();
      scanner.nextLine();
      String publisher = scanner.nextLine();
      int recommendedAge = scanner.nextInt();
      double price = scanner.nextDouble();
      scanner.nextLine();
      Book book = new Book(title, author, year, publisher, recommendedAge, price);
      this.books.add(book);
    }
  }
  public void printBooks() {
    for (Book book : this.books) {
      System.out.println(book);
    }
  }
  public void sortBooks() {
    Collections.sort(this.books);
  }

  public Book getBookPosition(int i) {
    return books.get(i);
  }

}