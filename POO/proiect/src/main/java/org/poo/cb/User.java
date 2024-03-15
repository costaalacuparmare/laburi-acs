package org.poo.cb;

import java.util.HashSet;
import java.util.HashMap;
import java.util.LinkedHashMap;

public class User {
  private final String firstName;
  private final String lastName;
  private final String email;
  private final String address;
  private boolean isPremium;
  private final HashMap<String, Account> accounts;
  private final HashMap<String, Integer> stocks;
  private final HashSet<String> friends;

  public User(UserBuilder builder) {
    this.firstName = builder.firstName;
    this.lastName = builder.lastName;
    this.email = builder.email;
    this.address = builder.address;
    this.accounts = new LinkedHashMap<>();
    this.stocks = new LinkedHashMap<>();
    this.friends = new HashSet<>();
  }

  public void setPremium(boolean isPremium) {
    this.isPremium = isPremium;
  }
  public boolean getPremium() {
    return this.isPremium;
  }

  public String getEmail() {
    return this.email;
  }

  public HashMap<String, Account> getAccounts() {
    return this.accounts;
  }

  public HashMap<String, Integer> getStocks() {
    return this.stocks;
  }

  public HashSet<String> getFriends() {
    return this.friends;
  }

  public String toStringUser() {
    StringBuilder sb = new StringBuilder();
    sb.append("{\"email\":\"").append(this.email);
    sb.append("\",\"firstname\":\"").append(this.firstName);
    sb.append("\",\"lastname\":\"").append(this.lastName);
    sb.append("\",\"address\":\"").append(this.address);
    sb.append("\",\"friends\":[");
    if (!this.friends.isEmpty()) {
      for (String friend : this.friends) {
        sb.append("\"").append(friend).append("\"");
        if (friend != this.friends.toArray()[this.friends.size() - 1]) {
          sb.append(",");
        }
      }
    }
    sb.append("]}");
    return sb.toString();
  }

  public String toStringPortfolio() {
    StringBuilder sb = new StringBuilder();
    sb.append("{\"stocks\":[");
    if (!this.stocks.isEmpty()) {
      for (String stock : this.stocks.keySet()) {
        sb.append("{\"stockName\":\"").append(stock);
        sb.append("\",\"amount\":").append(this.stocks.get(stock)).append("}");
        if (stock != this.stocks.keySet().toArray()[this.stocks.size() - 1]) {
          sb.append(",");
        }
      }
    }
    sb.append("],\"accounts\":[");
    if (!this.accounts.isEmpty()) {
      for (Account account : this.accounts.values()) {
        sb.append(account.toString());
        if (account !=
                this.accounts.values().toArray()[this.accounts.size() - 1]) {
          sb.append(",");
        }
      }
    }
    sb.append("]}");
    return sb.toString();
  }

  public static class UserBuilder {
    private String firstName;
    private String lastName;
    private final String email;
    private String address;

    public UserBuilder(String email) {
      this.email = email;
    }

    public UserBuilder firstName(String firstName) {
      this.firstName = firstName;
      return this;
    }

    public UserBuilder lastName(String lastName) {
      this.lastName = lastName;
      return this;
    }

    public UserBuilder address(String address) {
      this.address = address;
      return this;
    }

    public User build() {
      return new User(this);
    }
  }
}
