public class HawaiianPizza extends Pizza{
  public HawaiianPizza (int size, int price) {
    this.size = size;
    this.price = price;
  }
  public String toString() {
    return "Hawaiian, " + this.size + ", " + this.price;
  }
}
