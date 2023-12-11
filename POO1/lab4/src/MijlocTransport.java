public class MijlocTransport{
  private String culoare;
  private boolean functional;

  public MijlocTransport(String culoare, boolean functional) {
    this.culoare = culoare;
    this.functional = functional;
  }

  public MijlocTransport() {
    this.culoare = "alb";
    this.functional = false;
  }

  public String getCuloare() {
    return culoare;
  }

  public String toString() {
    return "Aceasta este culoarea " + this.culoare + "si functionalitatea: " + this.functional;
  }

  public void setCuloare(String culoare) {
    this.culoare = culoare;
  }

  public boolean isFunctional() {
    return functional;
  }

  public void setFunctional(boolean functional) {
    this.functional = functional;
  }

  public void setMijlocTransport(String culoare, boolean functional) {
    this.culoare = culoare;
    this.functional = functional;
  }

  public int incasare() {
    return 0;
  }

  public int profit() {
    return 0;
  }



}