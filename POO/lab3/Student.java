public class Student {
    private long NrMatricol;
    private String nume;
    private String prenume;
    private double MedieFinala;

    public Student() {

    }

    public long getNrMatricol() {
        return this.NrMatricol;
    }

    public void setNrMatricol(long NrMatricol) {
        this.NrMatricol = NrMatricol;
    }

    public String getNume() {
        return this.nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public String getPrenume() {
        return this.prenume;
    }

    public void setPrenume(String prenume) {
        this.prenume = prenume;
    }

    public double getMedieFinala(){
        return this.MedieFinala;
    }

    public void setMedieFinala(double MedieFinala){
        this.MedieFinala = MedieFinala;
    }

    public String detaliiStudent() {
        String detaliiStudent = "[" + this.NrMatricol + "] " + this.prenume + " " + this.nume + ": " + this.MedieFinala;
        return detaliiStudent;
    }

}