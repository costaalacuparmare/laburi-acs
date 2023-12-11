/**
 * The program computes the area and perimeter
 * of a circle with inputed variables with more options
 * Ex 2
 */
import java.util.Scanner;

public class ComputeAreaPerimeter {
    public static void main(String[] args) {
        System.out.println("Type in the radius: ");
        Scanner scanner = new Scanner(System.in);
        double radius = scanner.nextDouble();
        while (radius > 0) {
            System.out.println("Calculate perimeter (P) or area (A): ");
            scanner.skip("\n");
            // charAt(0) - takes char from that index in the nextLine string
            char option = scanner.nextLine().charAt(0);
            if (option == 'A') {
                double area;
                area = radius * radius * 3.14159;
                System.out.println("Area for the circle of R=" + radius + " is " + area);
            } else if (option == 'P') {
                double perimeter;
                perimeter = 2 * radius * 3.14159;
                System.out.println("Perimeter for the circle of R=" + radius + " is " + perimeter);
            }
            System.out.println("Input another radius: ");
            radius = scanner.nextDouble();
        }
        System.out.println("Inputed radius is negative!!!");
    }
}