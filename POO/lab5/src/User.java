public abstract class User {
  private String name;
  private int age = 0;

  protected User(String name, int age) {
    this.name = name;
    this.age = age;
  }
}