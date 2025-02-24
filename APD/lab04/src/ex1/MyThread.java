package ex1;

public class MyThread implements Runnable {
    private final int id;

    public MyThread(int id) {
        this.id = id;
    }

    @Override
    public void run() {
        System.out.println("Hello from thread #" + id);
    }
}