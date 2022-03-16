public class Logarithms {

    public static int log(int a, int b) {
        int i = 0;
        for (; b > 1; i++) {
            b = b / a;
        }
        if (b == 1) {
            return i;
        } else {
            return i - 1;
        }
    }
}
