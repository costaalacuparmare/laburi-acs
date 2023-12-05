import java.util.Random;
import java.util.Scanner;

public class Persoana {
    private static int nrPersoane;
    private ContBancar cont;
    private String nume, cnp;
    public void seteazaDate(String nume, String cnp, ContBancar cont)
            throws ExceptieCnpInvalid {
        if (cnp.length() != 13) {
            throw new ExceptieCnpInvalid("CNP-ul trebuie sa aiba 13 cifre");
        }
        if (cnp.charAt(0) != '1' || cnp.charAt(0) != '2') {
            throw new ExceptieCnpInvalid("CNP-ul trebuie sa inceapa cu" +
                                         "1 sau 2");
        }
        this.nume = nume;
        this.cnp = cnp;
        this.cont = cont;
    }
    public Persoana(String nume, String cnp, ContBancar cont) throws ExceptieCnpInvalid {
        seteazaDate(nume, cnp, cont);
        nrPersoane++;
    }
    public ContBancar cont() {
        return this.cont;
    }
    public void afiseazaInformatii() {
        System.out.println("nume: " + this.nume + "," + "cnp: " + this.cnp +
                           "," + "numar cont: " + this.cont.nrCont() + "," +
                           "depozit: " + this.cont.depozit());
    }
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        Random r = new Random();
        int n = r.nextInt(7) + 2;
        System.out.println("numar: " + n);
        Persoana[] persoane = new Persoana[n];
        for (int i = 0; i < n; i++) {
            try {
                System.out.println("nume: ");
                String nume = s.nextLine();
               String cnp = Long.toString(r.nextLong(5000000000000L - 1000000000000L + 1) + 1000000000000L);
                System.out.println("cnp: " + cnp);
                System.out.println("nr cont: ");
                int nrCont = s.nextInt();
                System.out.println("depozit: ");
                int depozitLaInceput = s.nextInt();

                ContBancar cont = new ContBancar(nrCont, depozitLaInceput);
                persoane[i] = new Persoana(nume, cnp, cont);
            } catch (ExceptieCnpInvalid ex) {
                System.out.println(ex.getMessage());
            }

        }
    }
}

class ExceptieCnpInvalid extends Exception {
    public ExceptieCnpInvalid(String message) {
        super(message);
    }
}
