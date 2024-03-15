package org.poo.cb;

public class AccountCAD implements Account{

  private final String currencyName;
  private double amount;

  public AccountCAD() {
    this.currencyName = "CAD";
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
    return String.format("{\"currencyName\":\"CAD\",\"amount\":\"%.2f\"}",
            this.amount);
  }
}
