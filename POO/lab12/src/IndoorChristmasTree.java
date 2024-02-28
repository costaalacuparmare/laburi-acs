public class IndoorChristmasTree extends TreeDecorator{
  public IndoorChristmasTree(Tree tree) {
    super(tree);
  }
  public void decorate() {
    super.decorate();
    System.out.println("Indoor decorations");
  }
}
