import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Check {

    public static void main(String[] args) throws FileNotFoundException {
        for(int testNum = 1; testNum <= 5; testNum++) {
            Scanner input = new Scanner(new File("teste/test" + testNum + ".in"));
            int n = input.nextInt();
            int capacitate = input.nextInt();
            
            int[] valori = new int[n];
            int[] greutati = new int[n];

            for (int i = 0; i < n; i++) {
                valori[i] = input.nextInt();
                greutati[i] = input.nextInt();
            }

            int rezultatAsteptat = input.nextInt();
            input.close();

            int rezultatObtinut = Rucsac.rucsac(valori, greutati, capacitate);

            if (rezultatObtinut == rezultatAsteptat) {
                System.out.println("Testul " + testNum + " reusit!");
            } else {
                System.out.println("Testul " + testNum + " esuat! Rezultat asteptat: " + rezultatAsteptat + ", Rezultat obtinut: " + rezultatObtinut);
            }
        }
    }
}
