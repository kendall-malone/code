public class StringMatching {
    
    public static int main(String s, String pattern) {
        for(int i = 0; i < s.length() - pattern.length() + 1; i++){
            if(s.startsWith(pattern, i)){
                return i;
            }
        }
        return -1;
    }
}
