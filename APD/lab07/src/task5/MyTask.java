package task5;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
    int[] colors;
    int step;

    public MyTask(int[] colors, int step) {
        this.colors = colors;
        this.step = step;
    }

    @Override
    protected Void compute() {
        if (step == Main.N) {
            Main.printColors(colors);
        } else {

            // for the node at position step try all possible colors
            List<MyTask> tasks = new ArrayList<>();
            for (int i = 0; i < Main.COLORS; i++) {
                int[] newColors = colors.clone();
                newColors[step] = i;
                if (task2.Main.verifyColors(newColors, step)) {
                    MyTask t = new MyTask(newColors, step + 1);
                    tasks.add(t);
                    t.fork();
                }
            }

            for (MyTask task : tasks) {
                task.join();
            }
        }

        return null;
    }
}