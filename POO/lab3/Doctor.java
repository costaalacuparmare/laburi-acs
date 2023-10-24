public class Doctor {
    private String nume;
    private int[] ratings;
    private int medieRating;
    Pacient[] pacient = new Pacient[3];
    public Doctor() {

    }

    public Pacient[] getPacient() {
        return pacient;
    }

    public void setPacient(Pacient[] pacient) {
        this.pacient = pacient;
    }

    public String getNume() {
        return nume;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public int[] getRatings() {
        return ratings;
    }

    public void setRatings(int[] ratings) {
        this.ratings = ratings;
    }

    public int getMedieRating() {
        return medieRating;
    }

    public void setMedieRating(int medieRating) {
        this.medieRating = medieRating;
    }

    public void adaugaRating(int rating) {
        int nrRatings = 0;
        int i = 0;
        while (this.ratings[i] != 0) {
            nrRatings++;
            i++;
        }
        this.ratings[nrRatings] = rating;
        nrRatings++;
        int sumaRatings = 0;
        for (i = 0; i < nrRatings; i++)
            sumaRatings += this.ratings[i];
        this.medieRating = sumaRatings / nrRatings;
    }

    public String afisareDoctor() {
        String afisareDoctor = this.nume + " " + this.medieRating + "\nPacientii doctorului sunt: \n";
        for(int i = 0; i < pacient.length; i++) {
            afisareDoctor += pacient[i].afisarePacient() + "\n";
        }
        return afisareDoctor;
    }

}