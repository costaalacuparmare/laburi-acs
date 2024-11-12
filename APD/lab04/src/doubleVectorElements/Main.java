package doubleVectorElements;

import java.sql.SQLOutput;

public class Main extends Thread {

    public static void main(String[] args) {


        for (int i = 0; i < MyThread.N; i++) {
            MyThread.v[i] = i;
        }

        Thread[] threads = new Thread[MyThread.P];

        for (int i = 0; i < MyThread.P; i++) {
            threads[i] = new Thread(new MyThread(i));
            threads[i].start();
        }

        for (int i = 0; i < MyThread.P; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        // Parallelize me using P threads


        for (int i = 0; i < MyThread.N; i++) {
            if (MyThread.v[i] != i * 2) {
                System.out.println("Wrong answer");
                System.exit(1);
            }
        }
        System.out.println("Correct");
    }

}
