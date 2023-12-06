public class SubsetSum {

  public static int subsetSum(int[] subSet, long K) {
    int i = 0;
    long sum = 0;
    for (;i < subSet.length;i++) {
      sum += subSet[i];
    }
    if (sum == K)
      return 1;
		return 0;
  }
}
