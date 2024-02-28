public class PizzaFactory {
  private static PizzaFactory instance;
  private PizzaFactory() {

  }

  public static PizzaFactory getInstance() {
    if (instance == null) {
      instance = new PizzaFactory();
    }
    return instance;
  }
  public enum PizzaType {
    Cheese,Diavola,Hawaiian,Ham;
  }
  public Pizza createPizza(PizzaType pizzaType, int size, int price) {
    return switch (pizzaType) {
      case Ham -> new HamPizza(size, price);
      case Diavola -> new DiavolaPizza(size, price);
      case Cheese -> new CheesePizza(size, price);
      case Hawaiian -> new HawaiianPizza(size, price);
    };
  }
}
