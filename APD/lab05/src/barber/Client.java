package barber;

public class Client extends Thread {
    private final int id;

    public Client(int id) {
        super();
        this.id = id;
    }

    @Override
    public void run() {
        try {
            Main.charsSemaphore.acquire();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        if (Main.chairs > 0) {
            // client occupies a seat
            Main.chairs--;

            System.out.println("Client " + id + " is waiting for haircut");
            System.out.println("Available seats: " + Main.chairs);

            Main.clientSemaphore.release();
            Main.charsSemaphore.release();
            try {
                Main.barberSemaphore.acquire();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            System.out.println("Client " + id + " is served by the barber");

            Main.leftClients[id] = Main.SERVED_CLIENT;
        } else {
            Main.charsSemaphore.release();
            System.out.println("Client " + id + " left unserved");
            Main.leftClients[id] = Main.UNSERVED_CLIENT;
        }
    }
}
