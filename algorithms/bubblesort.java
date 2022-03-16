public class Bubble {

    public static void sort(Comparable[] a){
        int n = a.length;
        for(int i = 0; i < n-1; i++){
            for(int j = 0; j < n-1; j++){
                if(less(a[j+1], a[j])){
                    exch(a, j, j+1);
                }
            }
        }
    }

    public static boolean less(Comparable v, Comparable w){
        return v.compareTo(w) < 0;
    }

    private static void exch(Object[] a, int i, int j){
        Object swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }
}
