public class Fibo {

    static int arrayFibo(int n) {
        int[] a = new int[n + 1];
        a[1] = 1;
        for (int i = 2; i <= n; i++) {
            a[i] = a[i-1] + a[i-2];
        }
        return a[n];
    }

    static int recursiveFibo(int n) {
        if (n < 2) {
            return n;
        }
        return recursiveFibo(n-1) + recursiveFibo(n - 2);
    }

    static int recursiveFibo2(int n) {
        if (n < 2) {
            return n;
        }
        return helper(0, 1, n-1);
    }

    static int helper(int a, int b, int n) {
        if (n == 0) {
            return b;
        }
        return helper(b, a+b, n-1);
    }

    static int closedFormFibo(int n) {
        double phi = (1 + Math.sqrt(5)) / 2;
        double psi = (1 - Math.sqrt(5)) / 2;
        return (int)Math.round((Math.pow(phi, n) - Math.pow(psi, n)) / Math.sqrt(5));
    }

    public static void main(String[] args) {
        System.out.println(arrayFibo(20));
    }

}
