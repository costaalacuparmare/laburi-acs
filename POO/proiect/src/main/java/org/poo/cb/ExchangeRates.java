package org.poo.cb;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class ExchangeRates implements Constants {
  private static ExchangeRates instance;
  private final double[][] rates;

  private ExchangeRates(int nrCurrencies) {
    this.rates = new double[nrCurrencies][nrCurrencies];
  }

  public static ExchangeRates getInstance() {
    if (instance == null) {
      instance = new ExchangeRates(5);
    }
    return instance;
  }

  public void loadRates(String exchangeRatesFile) throws IOException {
    BufferedReader br = new BufferedReader(new FileReader(exchangeRatesFile));
    String line;
    for(int i = 0; (line = br.readLine()) != null; ++i) {
      if (i == 0) {
        line = br.readLine();
      }
      String[] values = line.split(",");
      for(int j = 1; j < values.length; ++j) {
        this.rates[i][j - 1] = Double.parseDouble(values[j]);
      }
    }
    br.close();
  }

  private int getCurrencyIdx(String currency) {
    for(int i = 0; i < currencies.length; ++i) {
      if (currencies[i].equals(currency)) {
        return i;
      }
    }
    return -1;
  }

  public double getRate(String baseCurrency, String targetCurrency) {
    int baseIdx = this.getCurrencyIdx(baseCurrency);
    int targetIdx = this.getCurrencyIdx(targetCurrency);
    return baseIdx != -1 && targetIdx != -1 ? this.rates[baseIdx][targetIdx] : -1.0;
  }
}
