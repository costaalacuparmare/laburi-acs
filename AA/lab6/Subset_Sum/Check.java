import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Check {

    public static void main(String[] args) throws FileNotFoundException {
        for(int testNum = 1; testNum <= 5; testNum++) {
            Scanner input = new Scanner(new File("teste/test" + testNum + ".in"));
            int subSetLen = input.nextInt();
            long K = input.nextInt();
            
            int[] subSet = new int[subSetLen];

            for(int i = 0; i < subSetLen; i++) {
                subSet[i] = input.nextInt();
            }

            int rezultatAsteptat = input.nextInt();
            input.close();

            int rezultatObtinut = SubsetSum.subsetSum(subSet, K);

            if (rezultatObtinut == rezultatAsteptat) {
                System.out.println("Testul " + testNum + " reusit!");
            } else {
                System.out.println("Testul " + testNum + " esuat! Rezultat asteptat: " + rezultatAsteptat + ", Rezultat obtinut: " + rezultatObtinut);
            }
        }
    }
}
