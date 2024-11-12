package barber;

public class Barber extends Thread {
    @Override
    public void run() {
        int servedClients = 0;

        do {
            try {
                Main.clientSemaphore.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            try {
                Main.charsSemaphore.acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            Main.chairs++;

            Main.barberSemaphore.release();
            Main.charsSemaphore.release();

            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            System.out.println("Barber served client");
            ++servedClients;

        } while (checkIfThereAnyClients());
    }

    private boolean checkIfThereAnyClients() {
        int count = 0;
        for (var client: Main.leftClients) {
            if (client == 0) {
                count++;
            }
        }

        return count != 0;
    }
}
