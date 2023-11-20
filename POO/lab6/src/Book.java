public class Book {
  private String author;
  FirstPage firstPage;
  class FirstPage {
    private String poem;

    public FirstPage() {
      switch (Book.this.author) {
        case "Eminescu":
          this.poem = "Un cer de stele dedesubt\n" +
                  "Deasupra-i cer de stele\n" +
                  "Parea un fulger ne'ntrerupt\n" +
                  "Ratacitor prin ele\n";
          break;
        case "Alecsandri":
          this.poem = "In paduri trasnesc stejarii! E un ger amar, cumplit!\n" +
                  "Stelele par inghetate, cerul pare otelit\n" +
                  "Iar zapada cristalina pe campii stralucitoare\n" +
                  "Pare-un lan de diamanturi ce scartaie sub picioare\n";
          break;
        case "Cosbuc":
          this.poem = "Sunt copii. Cu multe sanii\n" +
                  "De pe coasta vin tipand\n" +
                  "Si se-mping si sar razand\n" +
                  "Prin zapada fac matanii\n" +
                  "Vrand-nevrand\n";
          break;
      }
    }

    public int numberVowels() {
      int count = 0;
      for (int i = 0; i < this.poem.length(); i++) {
        char c = Character.toLowerCase(poem.charAt(i));
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
          count++;
      }
      return count;
    }

    public String getPoem() {
      return this.poem;
    }

  }

    public Book(String author) {
      this.author = author;
      firstPage = new FirstPage();
    }

    public String toString() {
      String s = "Autor: " + this.author + "\n" + "Poem: " +
              firstPage.getPoem() + "\n" + "Numar vocale: " +
              firstPage.numberVowels() + "\n";
      return s;
    }
}