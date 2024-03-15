package org.poo.cb;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

public class StockValues {
  private static StockValues instance;
  private final HashMap<String, double[]> stockValues;

  private StockValues() {
    this.stockValues = new HashMap<>();
  }

  public static StockValues getInstance() {
    if (instance == null) {
      instance = new StockValues();
    }
    return instance;
  }

  public void loadStockValues(String stockValuesFile) {
    try (BufferedReader reader = new BufferedReader(new FileReader(stockValuesFile))) {
      String line;
      String[] headers = null;
      while ((line = reader.readLine()) != null) {
        String[] parts = line.split(",");
        if (headers == null) {
          headers = parts;
        } else {
          String stockName = parts[0];
          double[] values = new double[parts.length - 1];
          for (int i = 1; i < parts.length; i++) {
            values[i - 1] = Double.parseDouble(parts[i]);
          }
          stockValues.put(stockName, values);
        }
      }
    } catch (IOException | NumberFormatException e) {
      System.out.println("Error loading stock values");
      throw new RuntimeException(e);
    }
  }

  public HashMap<String, double[]> getStockValues() {
    return this.stockValues;
  }
}
