/**
 *  Input names and averages using arrays, then calculate the sum
 *  Ex 3 b)
 */
import java.util.Scanner;


public class Array {
    public static void main(String[] args) {
        System.out.println("Type in the number of students (below 11): ");
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        if (n <= 10) {
            double[][] array1 = new double[n][n];
            double[][] array2 = new double[n][n];
            for (int i = 0; i < array1.length; i++) {
                for (int j = 0; j < array1[i].length; j++) {
                    array1[i][j] = scanner.nextDouble();
                }
               }
            for (int i = 0; i < array2.length; i++) {
                for (int j = 0; j < array2[i].length; j++) {
                    array2[i][j] = scanner.nextDouble();
                }
            }
            double[][] sumArray = new double[n][n];
            for (int i = 0; i < sumArray.length; i++) {
                for (int j = 0; j < sumArray[i].length; j++) {
                    sumArray[i][j] = array1[i][j] + array2[i][j];
                }
            }
            for (int i = 0; i < sumArray.length; i++) {
                for (int j = 0; j < sumArray[i].length; j++) {
                    System.out.print(sumArray[i][j] + " ");
                }
                System.out.println();
            }
        } else {
            System.out.println("Number of students must be below 11");
        }
    }
}