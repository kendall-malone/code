public class Exponents {

    public static double pow(double a, int n) {
        if(n == 0) {
            return 1;
        }

        if(n % 2 == 0){
            double x = pow(a, n/2);
            return (x * x);
        }

        double x = pow(a, (n-1)/2);
        return(x * x * a);
    }

}
