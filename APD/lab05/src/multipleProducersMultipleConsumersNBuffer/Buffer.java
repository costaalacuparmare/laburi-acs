package multipleProducersMultipleConsumersNBuffer;

import java.util.Queue;

public class Buffer {
    
    Queue<Integer> queue;
    
    public Buffer(int size) {
        queue = new LimitedQueue<>(size);
    }

	public void put(int value) {
        synchronized (this) {
            try {
                while (!queue.isEmpty()) {
                    this.wait();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            queue.add(value);
            this.notifyAll();
        }
	}

	public int get() {
        synchronized (this) {
            try {
                while (queue.isEmpty()) {
                    this.wait();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            int a = -1;
            Integer result = queue.poll();
            if (result != null) {
                a = result;
            }
            this.notifyAll();
            return a;
        }
	}
}
