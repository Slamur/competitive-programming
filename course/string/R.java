import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Locale;
import java.util.StringTokenizer;

public class R {

    private void solve() {
        readInt(); // n
        int k = readInt();
        char[] s = readString().toCharArray();

        char[] t = getAnswer(s, k);
        out.println(new String(t));
    }

    private char[] getAnswer(char[] s, int k) {
        boolean[] used = new boolean[Character.MAX_VALUE + 1];
        for (char ch : s) {
            used[ch] = true;
        }

        char minUsed = '\0';
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (used[ch]) {
                minUsed = ch;
                break;
            }
        }

        char[] t = new char[k];
        System.arraycopy(s, 0, t, 0, Math.min(s.length, k));

        if (s.length < k) {
            Arrays.fill(t, s.length, k, minUsed);
        } else {
            char maxUsed = '\0';
            for (char ch = 'z'; ch >= 'a'; --ch) {
                if (used[ch]) {
                    maxUsed = ch;
                    break;
                }
            }

            int changedIndex = -1;
            for (int i = k - 1; i >= 0; --i) {
                if (t[i] != maxUsed) {
                    changedIndex = i;
                    break;
                }
            }

            for (char nextCh = (char)(t[changedIndex] + 1); nextCh <= 'z'; ++nextCh) {
                if (used[nextCh]) {
                    t[changedIndex] = nextCh;
                    break;
                }
            }

            Arrays.fill(t, changedIndex + 1, k, minUsed);
        }

        return t;
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
        new R().run();
    }
}
