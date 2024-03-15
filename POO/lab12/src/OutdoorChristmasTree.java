public class OutdoorChristmasTree extends TreeDecorator{
  public OutdoorChristmasTree(Tree tree) {
    super(tree);
  }
  public void decorate() {
    super.decorate();
    System.out.println("Outdoor decorations");
  }
}
