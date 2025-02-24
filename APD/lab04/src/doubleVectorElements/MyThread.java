package doubleVectorElements;

public class MyThread implements Runnable {
    private int id;

    static final Object lock = new Object();

    static int N = 100;

    static int P = 4; // the program should work for any P <= N

    public static int[] v = new int[N];

    public MyThread (int id) {
        this.id = id;
    }

    @Override
    public void run() {
        int start = this.id * N / P;
        int end = Math.min(((this.id + 1) * N / P), N);
        synchronized (lock) {
            for (int i = start; i < end; i++) {
                v[i] = v[i] * 2;
            }
        }
    }
}