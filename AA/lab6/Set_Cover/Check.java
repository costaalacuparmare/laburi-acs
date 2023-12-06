import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Check {

    public static void main(String[] args) throws FileNotFoundException {
        for(int testNum = 1; testNum <= 5; testNum++) {
            Scanner input = new Scanner(new File("teste/test" + testNum + ".in"));
            int universLength = input.nextInt();
            int numOfSubsets = input.nextInt();
            
            int[] universe = new int[universLength];
            ArrayList<Integer>[] subsets = new ArrayList[numOfSubsets];

            for(int i = 0; i < universLength; i++) {
                universe[i] = input.nextInt();
            }

            for(int i = 0; i < numOfSubsets; i++) {
                int subsetLength = input.nextInt();
                subsets[i] = new ArrayList<Integer>();
                for(int j = 0; j < subsetLength; j++) {
                    subsets[i].add(input.nextInt());
                }
            }

            int rezultatAsteptat = input.nextInt();
            input.close();

            int rezultatObtinut = SetCover.setCover(universe, subsets);

            if (rezultatObtinut == rezultatAsteptat) {
                System.out.println("Testul " + testNum + " reusit!");
            } else {
                System.out.println("Testul " + testNum + " esuat! Rezultat asteptat: " + rezultatAsteptat + ", Rezultat obtinut: " + rezultatObtinut);
            }
        }
    }
}
