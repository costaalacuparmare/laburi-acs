import java.util.*;

public class Main {
    public static void main(String[] args) {
        PizzaFactory pizzaFactory = PizzaFactory.getInstance();
        List<Pizza> pizzas = new ArrayList<>();
        pizzas.add(pizzaFactory.createPizza(PizzaFactory.PizzaType.Ham, 10, 100));
        pizzas.add(pizzaFactory.createPizza(PizzaFactory.PizzaType.Diavola, 20, 200));
        pizzas.add(pizzaFactory.createPizza(PizzaFactory.PizzaType.Cheese, 30, 300));
        pizzas.add(pizzaFactory.createPizza(PizzaFactory.PizzaType.Hawaiian, 40, 400));
        for (Pizza pizza : pizzas) {
            System.out.println(pizza);
        }

        System.out.println();

        MessageSet messageSet = new MessageSet();
        MessageObserver messageObserver = new MessageObserver(messageSet);
        messageSet.setMessage("Hello");
        messageSet.setMessage("How are you?");
        messageSet.setMessage("Ok, bye!");

        System.out.println();

        OutdoorChristmasTree outdoorChristmasTree = new OutdoorChristmasTree(new ChristmasTree());
        outdoorChristmasTree.decorate();
        IndoorChristmasTree indoorChristmasTree = new IndoorChristmasTree(new ChristmasTree());
        indoorChristmasTree.decorate();
    }
}
