package shortestPathsFloyd_Warshall;

public class MyThread implements Runnable{
    private int id;

    static int M = 9;

    static int N = 5;

    static int P = 7;

    static int[][] graph = {{0, 1, M, M, M},
            {1, 0, 1, M, M},
            {M, 1, 0, 1, 1},
            {M, M, 1, 0, M},
            {M, M, 1, M, 0}};

    static final Object lock = new Object();

    public MyThread (int id) {
        this.id = id;
    }

    @Override
    public void run() {
        int start = this.id * N / P;
        int end = Math.min(((this.id + 1) * N / P), N);
        synchronized (lock) {
            for (int k = start; k < end; k++) {
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
                    }
                }
            }
        }
    }
}