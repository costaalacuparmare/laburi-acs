package oneProducerOneConsumer;

import java.util.concurrent.Semaphore;

public class Buffer {
    private int a = -1;

    void put(int value) {
        synchronized (this) {
            try {
                while (a != -1) {
                    this.wait();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            a = value;
            this.notify();
        }
    }

    int get() {
        synchronized (this) {
            try {
                while (a == -1) {
                    this.wait();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            int a = this.a;
            this.a = -1;
            this.notify();
            return a;
        }
    }
}
