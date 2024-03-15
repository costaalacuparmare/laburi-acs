import java.io.BufferedReader;
import java.io.IOException;
import java.io.Serializable;

public class Auto implements Serializable {
  private String model;
  private int an;
  private int km;
  private double pret;

  public Auto(String model, int an, int k, double pret) {
    this.model = model;
    this.an = an;
    this.km = km;
    this.pret = pret;
  }
  public String getModel() {
    return this.model;
  }
  public void setModel(String model) {
    this.model = model;
  }
  public int getAn() {
    return this.an;
  }
  public void setAn(int an) {
    this.an = an;
  }
  public int getKm() {
    return this.km;
  }
  public void setKm(int km) {
    this.km = km;
  }
  public double getPret() {
    return this.pret;
  }
  public void setPret(double pret) {
    this.pret = pret;
  }
  public String toString() {
    return "Model: " + model + ", An: " + an + ", Km: " + km + ", Pret : " + pret;
  }
  public boolean identic(Auto a) {
    return (this.model.equals(a.model) && (this.an == a.an) && (this.km == a.km) && (this.pret == a.pret));
  }
  public static Auto citeste(BufferedReader br) throws IOException {
    try {
      String s = br.readLine();
      if (s == null)
        return null;
      return new Auto(s,Integer.parseInt(br.readLine()),
              Integer.parseInt(br.readLine()), Double.parseDouble(br.readLine()));
    } catch (IOException e) {
      e.printStackTrace();
    }
    return null;
  }
}
