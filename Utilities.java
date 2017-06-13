import java.util.Random;

public class Utilities {
    // Taken from https://stackoverflow.com/questions/2546078/java-random-long-number-in-0-x-n-range.
    public static long nextLong(Random rng, long n) {
        // error checking and 2^x checking removed for simplicity.
        long bits, val;
        do {
            bits = (rng.nextLong() << 1) >>> 1;
            val = bits % n;
        } while (bits-val+(n-1) < 0L);
        return val;
    }

}
