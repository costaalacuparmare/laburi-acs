public class InfluenzaDetector {

  Mucus mucus;
  static float influenzaAThreshold = 0.6f;
  static float influenzaBThreshold = 0.4f;
  static float covidThreshold = 0.7f;

  void checkAllFlyTypes(Mucus mucus) {
    this.mucus = mucus;

    class InfluenzaA {
      final Mucus mucus;

      InfluenzaA(Mucus mucus) {
        this.mucus = mucus;
      }

      public String getFluName() {
        if (mucus.type.name().equals("INFLUENZA_A"))
          return "INFLUENZA_A";
        return "NOT INFLUENZA_A";
      }

      public boolean isInfected() {
        if (mucus.type.name().equals("INFLUENZA_A")) {
          return mucus.percentage > influenzaAThreshold;
        }
        return false;
      }
    }

    class InfluenzaB {
      final Mucus mucus;

      InfluenzaB(Mucus mucus) {
        this.mucus = mucus;
      }

      public String getFluName() {
        if (mucus.type.name().equals("INFLUENZA_B"))
          return "INFLUENZA_B";
        return "NOT INFLUENZA_B";
      }

      public boolean isInfected() {
        if (mucus.type.name().equals("INFLUENZA_B")) {
          return mucus.percentage > influenzaBThreshold;
        }
        return false;
      }
    }

    class COVID {
      final Mucus mucus;

      COVID(Mucus mucus) {
        this.mucus = mucus;
      }

      public String getFluName() {
        if (mucus.type.name().equals("COVID"))
          return "COVID";
        return "NOT COVID";
      }

      public boolean isInfected() {
        if (mucus.type.name().equals("COVID")) {
          return mucus.percentage > covidThreshold;
        }
        return false;
      }
    }

    InfluenzaA fluA = new InfluenzaA(mucus);
    System.out.println(fluA.getFluName() + " result: Mucus is " + (fluA.isInfected() ? "Positive" : "either Negative or Unknown"));

    InfluenzaB fluB = new InfluenzaB(mucus);
    System.out.println(fluB.getFluName() + " result: Mucus is " + (fluB.isInfected() ? "Positive" : "either Negative or Unknown"));

    COVID covid = new COVID(mucus);
    System.out.println(covid.getFluName() + " result: Mucus is " + (covid.isInfected() ? "Positive" : "either Negative or Unknown"));

  }

}