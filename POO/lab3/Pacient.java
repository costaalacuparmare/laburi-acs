public class Pacient {
    private String nume;
    private int id;
    static int nr_pacient = 1;

    public Pacient() {
        this.id = this.nr_pacient++;
    }

    public String getNume() {
        return this.nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public int getId() {
	return this.id;
    }

    public void setId(int id) {
	this.id = id;
    }

    public String afisarePacient() {
        String afisarePacient = "[" + this.id + "] " + this.nume;
        return afisarePacient;
    }
}
