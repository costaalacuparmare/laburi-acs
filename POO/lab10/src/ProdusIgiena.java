public class ProdusIgiena extends Produs{
  double pretProducator;

  public ProdusIgiena(double pretProducator) {
    this.pretProducator = pretProducator;
  }

  @Override
  double pretRaft() {
    return pretProducator * 0.1 + pretProducator;
  }

  @Override
  void afiseaza() {
    System.out.println("ProdusIgiena cu pretul: " + pretRaft());
  }
}
