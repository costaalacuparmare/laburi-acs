public class TreeDecorator implements Tree{
  protected Tree tree;
  public TreeDecorator(Tree tree) {
    this.tree = tree;
  }
  public void decorate() {
    tree.decorate();
  }
}
