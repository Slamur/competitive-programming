import java.awt.Point;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class O {

    private void solve() {
        char[] s = readString().toCharArray();
        char[] t = readString().toCharArray();

        Point ans = getAnswer(s, t);

        String[] names = {
                "need tree", "automaton", "array", "both"
        };

        int nameIndex = ans.x | (ans.y << 1);
        out.println(names[nameIndex]);
    }

    Point getAnswer(char[] s, char[] t) {
        char start = 'a', end = 'z';
        int size = end - start + 1;

        int[] sCounts = new int[size];
        for (char ch : s) sCounts[ch - start]++;

        int[] tCounts = new int[size];
        for (char ch : t) tCounts[ch - start]++;

        int notNeeded = 0, needed = 1;
        Point needTree = new Point(notNeeded, notNeeded);

        boolean needRemove = false;
        for (int ch = 0; ch < size; ++ch) {
            int delta = sCounts[ch] - tCounts[ch];
            if (delta < 0) return needTree;
            if (delta > 0) {
                needRemove = true;
            }
        }

        int ti = 0;
        for (int si = 0; si < s.length && ti < t.length; ++si) {
            if (s[si] == t[ti]) {
                ++ti;
            }
        }

        boolean needSwap = (ti != t.length);

        return new Point(
                needRemove ? needed : notNeeded,
                needSwap ? needed : notNeeded
        );
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
        new O().run();
    }
}
