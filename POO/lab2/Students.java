/**
 *  Input names and averages and show them using vectors
 *  Ex 3 a)
 */
import java.util.Scanner;


public class Students {
    public static void main(String[] args) {
        System.out.println("Type in the number of students (below 11): ");
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        if (n <= 10) {
            String[] name = new String[n];
            double[] average = new double[n];
            for (int i = 0; i < n; i++) {
                scanner.skip("\n");
                name[i] = scanner.nextLine();
                average[i] = scanner.nextDouble();
            }
            for (int i = 0; i < n; i++)
                System.out.print(name[i] + " ");
            System.out.println();
            for (int i = 0; i < n; i++)
                System.out.print(average[i] + " ");
            System.out.println();
        } else {
            System.out.println("Number of students must be below 11");
        }
    }
}