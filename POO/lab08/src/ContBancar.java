public class ContBancar {
    private int numarCont;
    private int depozit;

    public ContBancar(int numarCont, int depozit) {
        this.numarCont = numarCont;
        this.depozit = depozit;
    }
    public void depune(int suma) {
        this.depozit += suma;
    }
    public void retrage(int suma) throws ExceptieFonduriInsuficiente{
        if (this.depozit < suma) {
            throw new ExceptieFonduriInsuficiente("Fonduri insuficiente");
        }
        this.depozit -= suma;
        System.out.println("Retrasa suma de " + suma + " lei");
    }
    public int nrCont() {
        return this.numarCont;
    }
    public int depozit() {
        return this.depozit;
    }

    public static void main(String[] args) {
        ContBancar cont = new ContBancar(123, 1000);
        cont.depune(1000);
        try {
            cont.retrage(1000);
        } catch (ExceptieFonduriInsuficiente e) {
            System.out.println(e.getMessage());
        }

        try {
            cont.retrage(2000);
        } catch (ExceptieFonduriInsuficiente e) {
            System.out.println(e.getMessage());
        }
    }
}

class ExceptieFonduriInsuficiente extends Exception {
    public ExceptieFonduriInsuficiente(String message) {
        super(message);
    }
}
