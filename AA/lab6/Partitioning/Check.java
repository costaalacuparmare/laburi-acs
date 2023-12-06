import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Check {

    public static void main(String[] args) throws FileNotFoundException {
        for(int testNum = 1; testNum <= 5; testNum++) {
            Scanner input = new Scanner(new File("teste/test" + testNum + ".in"));
            int subSet1Len = input.nextInt();
            int subSet2Len = input.nextInt();
            
            int[] subSet1 = new int[subSet1Len];
            int[] subSet2 = new int[subSet2Len];

            for(int i = 0; i < subSet1Len; i++) {
                subSet1[i] = input.nextInt();
            }
            for(int i = 0; i < subSet2Len; i++) {
                subSet2[i] = input.nextInt();
            }

            int rezultatAsteptat = input.nextInt();
            input.close();

            int rezultatObtinut = Partitioning.partitioning(subSet1, subSet2);

            if (rezultatObtinut == rezultatAsteptat) {
                System.out.println("Testul " + testNum + " reusit!");
            } else {
                System.out.println("Testul " + testNum + " esuat! Rezultat asteptat: " + rezultatAsteptat + ", Rezultat obtinut: " + rezultatObtinut);
            }
        }
    }
}
