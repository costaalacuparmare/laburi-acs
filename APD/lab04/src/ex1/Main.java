package ex1;
// Creați un program care să lanseze un număr de thread-uri egal cu numărul de
// core-uri de care dispune calculatorul vostru. Fiecare thread trebuie
// să afișeze la consolă un text de tipul "Hello from thread #id".

public class Main {
    public static void main(String[] args) {
        int N = Runtime.getRuntime().availableProcessors();
        Thread[] threads = new Thread[N];
        for (int i = 0; i < N; i++) {
            threads[i] = new Thread(new MyThread(i));
            threads[i].start();
        }
    }
}