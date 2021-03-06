import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class P {

    private void solve() {
        int tests = readInt();
        for (int test = 0; test < tests; ++test) {
            solveTest();
        }
    }

    private void solveTest() {
        long damage = readInt(), healPerSecond = readInt();
        long healDuration = readInt(), cooldown = readInt();

        long answer = getAnswer(damage, healPerSecond, healDuration, cooldown);
        out.println(answer);
    }

    long getAnswer(long damage, long healPerSecond, long healDuration, long cooldown) {
        if (damage > healPerSecond * healDuration) return -1;

        long healPerCooldown = healPerSecond * cooldown;

        /*
        f(k) = damage * k - healPerCooldown * (k * (k - 1) / 2)
        f(k) = -healPerCooldown / 2 * k^2 + k * (damage + healPerCooldown / 2)

        kOpt = -b / (2a) = -(damage + healPerCooldown / 2) / (-healPerCooldown / 2 * 2)
        kOpt = (2 * damage + healPerCooldown) / (2 * healPerCooldown)

        k in [1; healDuration / coolDown + 1]
         */

        long answer = 0;

        long kOpt = (2 * damage + healPerCooldown) / (2 * healPerCooldown);
        for (long k = Math.max(1, kOpt - 1); k <= Math.min(healDuration / cooldown + 1, kOpt + 1); ++k) {
            long maxHp = damage * k - healPerCooldown * (k * (k - 1) / 2);
            answer = Math.max(answer, maxHp);
        }

        return answer;
    }

    //////////////////////////////////////////////////////////////////

    long sqrtLong(long x) {
        long root = (long)Math.sqrt(x);
        while (root * root > x) --root;
        while ((root + 1) * (root + 1) <= x) ++root;
        return root;
    }

    //////////////////////////////////////////////////////////////////

    private boolean yesNo(boolean yes) {
        return yesNo(yes, "YES", "NO");
    }

    private boolean yesNo(boolean yes, String yesString, String noString) {
        out.println(yes ? yesString : noString);
        return yes;
    }

    //////////////////////////////////////////////////////////////////

    private long readLong() {
        return Long.parseLong(readString());
    }

    private int[] readIntArray(int n) {
        int[] a = new int[n];
        for (int i = 0; i < n; ++i) a[i] = readInt();
        return a;
    }

    private int readInt() {
        return Integer.parseInt(readString());
    }

    private String readString() {
        while (!tok.hasMoreTokens()) {
            String nextLine = readLine();
            if (null == nextLine) return null;
            tok = new StringTokenizer(nextLine);
        }

        return tok.nextToken();
    }

    private String readLine() {
        try {
            return in.readLine();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    //////////////////////////////////////////////////////////////////

    private BufferedReader in;
    private StringTokenizer tok;
    private PrintWriter out;

    private void initFileIO(String inputFileName, String outputFileName) throws FileNotFoundException {
        in = new BufferedReader(new FileReader(inputFileName));
        out = new PrintWriter(outputFileName);
    }

    private void initConsoleIO() throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
    }

    private void initIO() throws IOException {
        Locale.setDefault(Locale.US);

        String fileName = "";

        if (!fileName.isEmpty()) {
            initFileIO(fileName + ".in", fileName + ".out");
        } else {
            if (new File("input.txt").exists()) {
                initFileIO("input.txt", "output.txt");
            } else {
                initConsoleIO();
            }
        }

        tok = new StringTokenizer("");
    }

    //////////////////////////////////////////////////////////////////

    private void run() {
        try {
            long timeStart = System.currentTimeMillis();

            initIO();
            solve();
            out.close();

            long timeEnd = System.currentTimeMillis();
            System.err.println("Time(ms) = " + (timeEnd - timeStart));
        } catch (Exception e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        new P().run();
    }
}
