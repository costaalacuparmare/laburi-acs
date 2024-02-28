public class CheesePizza extends Pizza{
  public CheesePizza (int size, int price) {
    this.size = size;
    this.price = price;
  }
  public String toString() {
    return "Cheese, " + this.size + ", " + this.price;
  }
}
