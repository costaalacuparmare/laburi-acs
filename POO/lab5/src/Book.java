public class Book implements Comparable, Buyer {
  int recommendedAge = 0;
  double price;
  private String title;
  private String author;
  private int year = 0;
  private String publisher;

  public Book() {
  }

  public Book(String title, String author, int year, String publisher,
              int recommendedAge, double price) {
    this.title = title;
    this.author = author;
    this.year = year;
    this.publisher = publisher;
    this.recommendedAge = recommendedAge;
    this.price = price;
  }

  public String toString() {
    return title + " by " + author + " (" + year + ") published by " +
            publisher + " for age " + recommendedAge + " and up" + "for " + price;
  }

  public int getRecommendedAge() {
    return recommendedAge;
  }

  public int compareTo(Object o) {
    if (this.recommendedAge > ((Book) o).recommendedAge)
      return 1;
    else if (this.recommendedAge < ((Book) o).recommendedAge)
      return -1;
    return 0;
  }

  public void buyBook(User user) {
    if (user instanceof Student) {
      this.price = this.price * 0.95;
    }
    if (user instanceof Teacher) {
      this.price = this.price * 0.9;
    }
    if (user instanceof Librarian) {
      this.price = this.price * 0.7;
    }
  }

}

