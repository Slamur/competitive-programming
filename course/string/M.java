import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class M {

    private void solve() {
        char[] s = readString().toCharArray();

        int m = readInt();
        int[] a = readIntArray(m);
        for (int i = 0; i < m; ++i) --a[i];

        char[] ans = getAnswer(s, a);
        out.println(new String(ans));
    }

    char[] getAnswer(char[] s, int[] a) {
        int n = s.length;

        boolean[] swapped = new boolean[n / 2 + 1];
        for (int index : a) {
            swapped[index] = !swapped[index];
        }

        for (int index = 1; index < swapped.length; ++index) {
            if (swapped[index - 1]) {
                swapped[index] = !swapped[index];
            }
        }

        for (int i = 0, j = n - 1; i < j; ++i, --j) {
            if (swapped[i]) {
                char tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }

        return s;
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
        new M().run();
    }
}
