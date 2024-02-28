public class DiavolaPizza extends Pizza{
  public DiavolaPizza (int size, int price) {
    this.size = size;
    this.price = price;
  }
  public String toString() {
    return "Diavola, " + this.size + ", " + this.price;
  }
}
