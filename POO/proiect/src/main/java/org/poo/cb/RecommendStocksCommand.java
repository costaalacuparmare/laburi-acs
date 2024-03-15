package org.poo.cb;

import java.util.HashMap;
import java.util.HashSet;

public class RecommendStocksCommand implements Command {

  private final HashMap<String, double[]> stockValues;
  private final HashSet<String> recommendedStocks;

  public RecommendStocksCommand(HashSet<String> recommendedStocks) {
    this.stockValues = StockValues.getInstance().getStockValues();
    this.recommendedStocks = recommendedStocks;
  }

  private double calculateSMA(double[] values, int startIdx, int endIdx) {
    double sum = 0;
    for (int i = startIdx; i < endIdx; i++) {
      sum += values[i];
    }
    return sum / (endIdx - startIdx);
  }

  public void printRecommendedStocks() {
    System.out.print("{\"stocksToBuy\":[");
    for (String stock : recommendedStocks) {
      System.out.print("\"" + stock + "\"");
      if (stock != recommendedStocks.toArray()[recommendedStocks.size() - 1]) {
        System.out.print(",");
      }
    }
    System.out.println("]}");
  }

  public void execute() {
    for (String stock : this.stockValues.keySet()) {
      double[] values = this.stockValues.get(stock);
      double shortTermSMA = calculateSMA(values,
              values.length - 5, values.length);
      double longTermSMA = calculateSMA(values,
              values.length - 10, values.length);
      if (shortTermSMA > longTermSMA) {
        recommendedStocks.add(stock);
      }
    }
    printRecommendedStocks();
  }

}
