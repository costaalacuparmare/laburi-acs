import java.util.*;

public class MessageSet {
  public List<String> messageList;
  private Observer observer;
public MessageSet() {
    this.messageList = new ArrayList<String>();
  }
  public void notifyObserver() {
    if (observer != null)
      observer.update();
  }
  public void setMessage(String message) {
    if (messageList.size() >= 10) {
      messageList.remove(0); // Remove the oldest message if the list is full
    }
    messageList.add(message);
    notifyObserver();
  }

  public String getMessage() {
    if (messageList.isEmpty()) {
      return "No messages available.";
    }
    return messageList.get(messageList.size() - 1);
  }
  public void attach(Observer observer) {
    this.observer = observer;
  }
}
