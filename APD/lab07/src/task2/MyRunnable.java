package task2;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {
    int[] colors;
    ExecutorService tpe;
    AtomicInteger inQueue;
    Integer step;

    public MyRunnable(int[] colors, ExecutorService tpe,
                      AtomicInteger inQueue, Integer step) {
        this.colors = colors;
        this.tpe = tpe;
        this.inQueue = inQueue;
        this.step = step;
    }

    @Override
    public void run() {
        if (step == Main.N) {
            Main.printColors(colors);
        } else {

            // for the node at position step try all possible colors
            for (int i = 0; i < Main.COLORS; i++) {
                int[] newColors = colors.clone();
                newColors[step] = i;
                if (Main.verifyColors(newColors, step)) {
                    inQueue.incrementAndGet();
                    tpe.submit(new MyRunnable(newColors, tpe, inQueue, step + 1));
                }
            }
        }

        int left = inQueue.decrementAndGet();
        if (left == 0) {
            tpe.shutdown();
        }
    }
}