public class ProdusCuratenie extends Produs{
  double pretProducator;

  public ProdusCuratenie(double pretProducator) {
    this.pretProducator = pretProducator;
  }

  @Override
  double pretRaft() {
    return pretProducator * 0.15 + pretProducator;
  }

  @Override
  void afiseaza() {
    System.out.println("ProdusCuratenie cu pretul: " + pretRaft());
  }
}
