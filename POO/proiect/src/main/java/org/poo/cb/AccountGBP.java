package org.poo.cb;

public class AccountGBP implements Account{

  private final String currencyName;
  private double amount;

  public AccountGBP() {
    this.currencyName = "GBP";
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
    return String.format("{\"currencyName\":\"GBP\",\"amount\":\"%.2f\"}",
            this.amount);
  }
}
