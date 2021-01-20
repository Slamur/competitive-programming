import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class S {

    private void solve() {
        readInt(); // len
        char[] hidden = readString().toCharArray();

        int m = readInt();
        char[][] words = new char[m][];
        for (int i = 0; i < m; ++i) {
            words[i] = readString().toCharArray();
        }

        int answer = getAnswer(hidden, words);
        out.println(answer);
    }

    private int getAnswer(char[] hidden, char[][] words) {
        final char unknown = '*';

        boolean[] revealed = new boolean[Character.MAX_VALUE + 1];
        for (char ch : hidden) {
            if (unknown != ch) {
                revealed[ch] = true;
            }
        }

        int[] counts = new int[Character.MAX_VALUE + 1];
        int activeWordsCount = 0;

        for (char[] word : words) {
            boolean possible = true;
            for (int i = 0; i < word.length; ++i) {
                char wordCh = word[i];
                char hiddenCh = hidden[i];

                if (unknown == hiddenCh) {
                    possible &= !revealed[wordCh];
                } else {
                    possible &= (wordCh == hiddenCh);
                }
            }

            if (!possible) continue;

            ++activeWordsCount;

            boolean[] waiting = new boolean[Character.MAX_VALUE + 1];
            for (char ch : word) {
                if (!revealed[ch]) waiting[ch] = true;
            }

            for (char ch = 'a'; ch <= 'z'; ++ch) {
                if (waiting[ch]) ++counts[ch];
            }
        }

        int ans = 0;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (activeWordsCount == counts[ch]) {
                ++ans;
            }
        }

        return ans;
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
        new S().run();
    }
}
