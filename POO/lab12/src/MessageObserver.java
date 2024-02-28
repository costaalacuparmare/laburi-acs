public class MessageObserver implements Observer {
  private final MessageSet subject;

  public MessageObserver(MessageSet subject) {
    this.subject = subject;
    this.subject.attach(this);
  }

  @Override
  public void update() {
    System.out.println("Latest message: " + subject.getMessage());
  }
}
