public class ProdusAlimentar extends Produs{
  double pretProducator;

  public ProdusAlimentar(double pretProducator) {
    this.pretProducator = pretProducator;
  }

  @Override
  double pretRaft() {
    return pretProducator * 0.2 + pretProducator;
  }

  @Override
  void afiseaza() {
    System.out.println("ProdusAlimentar cu pretul: " + pretRaft());
  }
}
