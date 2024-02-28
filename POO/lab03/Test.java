import java.util.Scanner;

public class Test {
    public static void main(String[] args) {
        // Pentru Ex1/ Student
        Student student1 = new Student();
        student1.setNrMatricol(1);
        student1.setNume("Ion");
        student1.setPrenume("Ionescu");
        student1.setMedieFinala(9.8);

        Student student2 = new Student();
        student2.setNrMatricol(2);
        student2.setNume("Andrei");
        student2.setPrenume("Popescu");
        student2.setMedieFinala(8.7);

        Student student3 = new Student();
        student3.setNrMatricol(3);
        student3.setNume("Matei");
        student3.setPrenume("Flop");
        student3.setMedieFinala(9.5);

        Student[] studenti = new Student[3];
        studenti[0] = student1;
        studenti[1] = student2;
        studenti[2] = student3;

        double  medieStudenti = 0;
        for( int i = 0; i < studenti.length; i++) {
            medieStudenti += studenti[i].getMedieFinala();
            System.out.println(studenti[i].detaliiStudent());
        }

        medieStudenti /= studenti.length;

        System.out.println("Media studentilor este: " + medieStudenti);
        System.out.println();

        //Ex2 / doctor
        Pacient[] pacienti = new Pacient[3];
        pacienti[0] = new Pacient();
        pacienti[0].setNume("Matei Popescu");
        pacienti[1] = new Pacient();
        pacienti[1].setNume("Andrei Marcu");
        pacienti[2] = new Pacient();
        pacienti[2].setNume("Ion Tudorescu");

        for(int i = 0; i < 3; i++) {
            System.out.println(pacienti[i].afisarePacient());
        }
        System.out.println();

        //Ex3 - Medic de familie
        Doctor doctor1 = new Doctor();
        doctor1.setNume("Popescu Ion");
        int[] ratings = new int[5];
        ratings[0] = 8;
        ratings[1] = 9;
        ratings[2] = 10;
        int medie = 9;
        doctor1.setRatings(ratings);
        doctor1.setMedieRating(medie);
        doctor1.setPacient(pacienti);
        System.out.println("Medie: " + doctor1.getMedieRating());

        int rating = 5;
        doctor1.adaugaRating(rating);
        System.out.println("Noua medie: " + doctor1.getMedieRating());
        System.out.println(doctor1.afisareDoctor());

    }
}