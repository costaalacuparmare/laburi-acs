public class Demo {
    public static void main(String[] args) {
        float a = 100.25f;
        long b = (long)a;
        System.out.println("value of a: "+a);
        System.out.println("value of b: "+b);
        int c = (int)b;
        System.out.println("value of c: "+c);
        byte d = (byte)c;
        System.out.println("value of d: "+d);
    }
}