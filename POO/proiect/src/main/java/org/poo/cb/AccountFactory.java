package org.poo.cb;

public class AccountFactory {
  private static AccountFactory instance;

  private AccountFactory() {
  }

  public static AccountFactory getInstance() {
    if (instance == null) {
      instance = new AccountFactory();
    }
    return instance;
  }

  public Account createAccount(String currency) {
    return switch (currency) {
      case "CAD" -> new AccountCAD();
      case "EUR" -> new AccountEUR();
      case "GBP" -> new AccountGBP();
      case "JPY" -> new AccountJPY();
      case "USD" -> new AccountUSD();
      default -> null;
    };
  }
}
