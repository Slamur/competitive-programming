import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.StringTokenizer;

public class H {

    private void solve() {
        int n = 3;
        String[] parts = new String[n];
        for (int i = 0; i < parts.length; ++i) {
            parts[i] = readString();
        }

        int q = readInt();
        String[] queries = new String[q];
        for (int i = 0; i < q; ++i) {
            queries[i] = readString();
        }

        boolean[] answers = getAnswers(parts, queries);
        for (boolean answer : answers) {
            yesNo(answer, "ACC", "WA");
        }
    }

    final String SIGNS = "-;_";

    String refine(String s) {
        for (char sign : SIGNS.toCharArray()) {
            s = s.replace("" + sign, "");
        }

        s = s.toLowerCase();

        return s;
    }

    boolean[] getAnswers(String[] parts, String[] queries) {
        int n = parts.length;
        for (int i = 0; i < n; ++i) {
            parts[i] = refine(parts[i]);
        }

        String a = parts[0], b = parts[1], c = parts[2];

        String[] permutations = {
                a + b + c,
                a + c + b,
                b + a + c,
                b + c + a,
                c + a + b,
                c + b + a
        };

        boolean[] answers = new boolean[queries.length];
        for (int i = 0; i < queries.length; ++i) {
            String query = refine(queries[i]);

            for (String permutation : permutations) {
                answers[i] |= permutation.equals(query);
            }
        }

        return answers;
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
        new H().run();
    }
}
