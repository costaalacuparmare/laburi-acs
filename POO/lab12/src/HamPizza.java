public class HamPizza extends Pizza{
  public HamPizza (int size, int price) {
    this.size = size;
    this.price = price;
  }
  public String toString() {
    return "Ham, " + this.size + ", " + this.price;
  }
}
