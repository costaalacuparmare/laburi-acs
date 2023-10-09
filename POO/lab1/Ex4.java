public class Ex4 {
    public static void main(String[] args) {
        int a = 5;
        System.out.println(a + -a - a++ % 10);
        System.out.println(a - a + --a / 10);
        for (int i = 2; i < 5;) {
            i++;
            a += a;
        }
        System.out.println("a = " + a);
    }
}