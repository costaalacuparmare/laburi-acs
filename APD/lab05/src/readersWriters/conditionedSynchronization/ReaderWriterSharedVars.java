package readersWriters.conditionedSynchronization;

import java.util.concurrent.Semaphore;

public class ReaderWriterSharedVars {
    // The value to read/write
    volatile int shared_value;
    // Add semaphores and anything else needed for synchronization
    final Semaphore s;

    ReaderWriterSharedVars(int init_shared_value) {
        this.shared_value = init_shared_value;
        this.s = new Semaphore(1);
    }

}
