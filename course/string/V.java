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

public class V {

    private void solve() {
        int n = readInt();
        int size = 2 * n - 2;
        String[] s = new String[size];
        for (int i = 0; i < size; ++i) {
            s[i] = readString();
        }

        boolean[] isSuffixes = getIsSuffixes(s);
        for (boolean isSuffix : isSuffixes) {
            out.print(isSuffix ? 'S' : 'P');
        }
    }

    boolean[] getIsSuffixes(String[] words) {
        int length = words.length / 2 + 1;

        Point[] lenToIndexes = new Point[length];
        for (int len = 1; len < length; ++len) {
            lenToIndexes[len] = new Point(-1, -1);
        }

        for (int i = 0; i < words.length; ++i) {
            int len = words[i].length();

            Point indexes = lenToIndexes[len];
            if (-1 == indexes.x) indexes.x = i;
            else indexes.y = i;
        }

        String max1 = words[lenToIndexes[length - 1].x];
        String max2 = words[lenToIndexes[length - 1].y];

        boolean[] isSuffixes = getIsSuffixes(max1, max2, words, lenToIndexes);
        if (null == isSuffixes) {
            isSuffixes = getIsSuffixes(max2, max1, words, lenToIndexes);
        }

        return isSuffixes;
    }

    boolean[] getIsSuffixes(String prefix, String suffix, String[] words, Point[] lenToIndexes){
        String prefixCommon = prefix.substring(1);
        String suffixCommon = suffix.substring(0, suffix.length() - 1);

        if (!prefixCommon.equals(suffixCommon)) return null;

        String total = prefix.charAt(0) + suffix;

        boolean[] isSuffixes = new boolean[words.length];
        for (int len = 1; len < total.length(); ++len) {
            int first = lenToIndexes[len].x, second = lenToIndexes[len].y;
            String firstWord = words[first], secondWord = words[second];

            boolean firstPrefix = total.startsWith(firstWord), firstSuffix = total.endsWith(firstWord);
            boolean secondPrefix = total.startsWith(secondWord), secondSuffix = total.endsWith(secondWord);

            if (firstPrefix && secondSuffix) {
                isSuffixes[first] = false;
                isSuffixes[second] = true;
            } else if (firstSuffix && secondPrefix) {
                isSuffixes[first] = true;
                isSuffixes[second] = false;
            } else {
                return null;
            }
        }

        return isSuffixes;
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
        new V().run();
    }
}
