package org.poo.cb;

public class AccountEUR implements Account{

  private final String currencyName;
  private double amount;

  public AccountEUR() {
    this.currencyName = "EUR";
  }

  @Override
  public void deposit(double amount) {
    this.amount += amount;
  }
  @Override
  public void withdraw(double amount) {
    this.amount -= amount;
  }
  @Override
  public double getAmount() {
    return this.amount;
  }
  @Override
  public String getCurrency() {
    return this.currencyName;
  }
  @Override
  public String toString() {
    return String.format("{\"currencyName\":\"EUR\",\"amount\":\"%.2f\"}",
            this.amount);
  }
}
