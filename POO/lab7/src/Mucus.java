public class Mucus {

  enum FluType {
    INFLUENZA_A,
    INFLUENZA_B,
    COVID
  };

  FluType type;
  float percentage;

  public Mucus(FluType type, float percentage) {
    this.type = type;
    this.percentage = percentage < 1 ? (percentage > 0 ? percentage : 0) : 1;
  }

  @Override
  public String toString() {
    return "Mucus information: " +
            "type = " + type +
            ", percentage = " + (int)(percentage * 100) + '%';
  }
}