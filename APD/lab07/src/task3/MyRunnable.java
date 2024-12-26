package task3;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {
    int[] graph;
    ExecutorService tpe;
    AtomicInteger inQueue;
    Integer step;

    public MyRunnable(int[] graph, ExecutorService tpe,
                      AtomicInteger inQueue, Integer step) {
        this.graph = graph;
        this.tpe = tpe;
        this.inQueue = inQueue;
        this.step = step;
    }

    @Override
    public void run() {
        if (Main.N == step) {
            Main.printQueens(graph);
        } else {
            for (int i = 0; i < Main.N; ++i) {
                int[] newGraph = graph.clone();
                newGraph[step] = i;

                if (Main.check(newGraph, step)) {
                    inQueue.incrementAndGet();
                    tpe.submit(new MyRunnable(newGraph, tpe, inQueue, step + 1));
                }
            }
        }

        int left = inQueue.decrementAndGet();
        if (left == 0) {
            tpe.shutdown();
        }
    }
}