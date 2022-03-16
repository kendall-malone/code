public class BloomFilter<K> {

    private long[] bits;

    public BloomFilter(){
        bits = new long[1024];
    }

    public void add (K key){
        int index, bit;

        int hashCode = key.hashCode();
        int higherOrder = hashCode  >>> 16;
        int lowerOrder = (hashCode & 0x0000FFFF);

        index = lowerOrder / 64;
        bit = lowerOrder % 64;

        bits[index] |= 1L << bit;

        index = higherOrder / 64;
        bit = higherOrder % 64;

        bits[index] |= 1L << bit;
    }

    public boolean mightContain(K key){
        int index, bit;

        int hashCode = key.hashCode();
        int higherOrder = hashCode  >>> 16;
        int lowerOrder = (hashCode & 0x0000FFFF);

        index = lowerOrder / 64;
        bit = lowerOrder % 64;

        if((bits[index] & 1L << bit) == 0){
            return false;
        }

        index = higherOrder / 64;
        bit = higherOrder % 64;
        if((bits[index] & 1L << bit) == 0){
            return false;
        }
        return true;
    }

    public int trueBits(){
        int count = 0;
        for (int i = 0; i < 1024; i++) {
            count += Long.bitCount(bits[i]);
        }
        return count;
    }
}
