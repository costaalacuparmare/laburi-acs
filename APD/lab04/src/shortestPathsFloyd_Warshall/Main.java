package shortestPathsFloyd_Warshall;

public class Main extends Thread{

    public static void main(String[] args) {
        // Parallelize me (You might want to keep the original code in order to compare)
//        for (int k = 0; k < 5; k++) {
//            for (int i = 0; i < 5; i++) {
//                for (int j = 0; j < 5; j++) {
//                    graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
//                }
//            }
//        }

        Thread[] threads = new Thread[MyThread.P];

        for (int i = 0; i < MyThread.P; i++) {
            threads[i] = new Thread(new doubleVectorElements.MyThread(i));
            threads[i].start();
        }

        for (int i = 0; i < MyThread.P; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                System.out.print(MyThread.graph[i][j] + " ");
            }
            System.out.println();
        }
    }
}
