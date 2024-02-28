import java.io.*;

public class ParcAuto implements Serializable {
  private String numeFisier;

  public ParcAuto(String numeFisier) {
    this.numeFisier = numeFisier;
  }
  public int NumaraMasiniNoi() throws IOException {
    FileReader fr = new FileReader(numeFisier);
    BufferedReader br = new BufferedReader(fr);
    int nr = 0;
    while (true) {
      Auto a = Auto.citeste(br);
      if (a == null)
        break;
      if (a.getKm() == 0)
        nr++;
    }
    br.close();
    fr.close();
    return nr;
  }
  public void adaugaAuto(Auto a) throws IOException{
    FileWriter fw = new FileWriter(numeFisier, true);
    PrintWriter pw = new PrintWriter(fw);
    pw.println(a.getModel());
    pw.println(a.getAn());
    pw.println(a.getKm());
    pw.println(a.getPret());
    pw.close();
    fw.close();
  }
  public boolean cauta(Auto a) throws IOException {
    FileReader fr = new FileReader(numeFisier);
    BufferedReader br = new BufferedReader(fr);
    while (true) {
      Auto b = Auto.citeste(br);
      if (b == null)
        break;
      if (b.identic(a)) {
        br.close();
        fr.close();
        return true;
      }
    }
    br.close();
    fr.close();
    return false;
  }
  public String toString() {
    String s = null;
    FileReader fr = null;
    try {
      fr = new FileReader(numeFisier);
    } catch (FileNotFoundException e) {
      throw new RuntimeException(e);
    }
    BufferedReader br = new BufferedReader(fr);
    while (true) {
      Auto a = null;
      try {
        a = Auto.citeste(br);
      } catch (IOException e) {
        throw new RuntimeException(e);
      }
      if (a == null)
        break;
      if (s == null)
        s = a.toString();
      else
        s = s + "\n" + a.toString();
    }
    return s;
  }
  public boolean verificaFisierBinar() {
    ObjectOutputStream os = null;
    try {
      os = new ObjectOutputStream(new FileOutputStream("data.bin"));
      os.writeObject(this);
    } catch (IOException e) {
      e.printStackTrace();
    } finally {
      if (os != null)
        try {
        os.close();
        } catch (IOException e) {
          e.printStackTrace();
        }
    }

    ObjectInputStream is = null;
    ParcAuto p = null;
    try {
      is = new ObjectInputStream(new FileInputStream("data.bin"));
      p = (ParcAuto) is.readObject();
    } catch (IOException | ClassNotFoundException e) {
      throw new RuntimeException(e);
    }
    return this.toString().equals(p.toString());
  }
}
