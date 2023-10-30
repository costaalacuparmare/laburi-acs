public class Autobuz extends MijlocTransport {
  private int numarPasageri;
  private int pretBilet;
  private int intretinerePerBilet;

  public Autobuz(String culoare, boolean functional, int
          numarPasageri, int pretBilet, int intretinerePerBilet) {
    super(culoare, functional);
    this.numarPasageri = numarPasageri;
    this.pretBilet = pretBilet;
    this.intretinerePerBilet = intretinerePerBilet;
  }

  public String toString() {
    return "Autobuz: (" + this.getCuloare() + ", " +
            this.isFunctional() + ") cu " +
            this.numarPasageri + " si " +
            pretBilet + " are profit: " +
            this.profit();
  }

  public int incasare() {
    return this.numarPasageri * this.pretBilet;
  }

  public int profit() {
    return (this.incasare() - this.numarPasageri * this.intretinerePerBilet) / 4;
  }



}