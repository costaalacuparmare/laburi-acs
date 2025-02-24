package multipleProducersMultipleConsumers;

//Use ArrayBlockingQueue

import java.util.concurrent.ArrayBlockingQueue;

public class Buffer {
    ArrayBlockingQueue<Integer> buffer = new ArrayBlockingQueue<Integer>(10);
	void put(int value) {
        try {
            buffer.put(value);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
	}

	int get() {
        try {
            return buffer.take();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return -1;
	}
}
