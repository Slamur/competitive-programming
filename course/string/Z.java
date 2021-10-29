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
import java.util.function.BiFunction;

public class Z {

    private void solve() {
        String s = readString();
        String t = readString();

        String answer = getAnswer(s, t);
        if (answer.compareTo(t) <= 0) answer = "-1";
        out.println(answer);
    }

    String getAnswer(String s, String t) {
        char none = '\0';

        if (t.length() < s.length()) {
            t += ("" + none).repeat(s.length() - t.length());
        }

        int[] sCounts = new int[1 << 8];
        for (char ch : s.toCharArray()) sCounts[ch]++;

        char[] answer = new char[s.length()];
        Arrays.fill(answer, none);

        String finalT = t;
        BiFunction<Integer, Character, Boolean> canBeGreater = (startIndex, startCh) -> {
            answer[startIndex] = startCh;
            --sCounts[startCh];

            int index = startIndex + 1;
            for (char ch = 'z'; ch >= 'a'; --ch) {
                for (int it = 0; it < sCounts[ch]; ++it) {
                    answer[index++] = ch;
                }
            }

            boolean can = new String(answer).compareTo(finalT) > 0;

            answer[startIndex] = none;
            ++sCounts[startCh];

            return can;
        };

        boolean prefixEquals = true;
        for (int index = 0; index < answer.length; ++index) {
            char tCh = t.charAt(index);

            char startCh = 'a';
            if (prefixEquals && none != tCh) {
                startCh = tCh;
            }

            char usedCh = none;
            for (char ch = startCh; ch <= 'z'; ++ch) {
                if (0 == sCounts[ch]) continue;

                if (canBeGreater.apply(index, ch)) {
                    usedCh = ch;
                    break;
                }
            }

            if (none == usedCh) {
                return "";
            }

            prefixEquals &= (tCh == usedCh);
            answer[index] = usedCh;
            --sCounts[usedCh];
        }

        return new String(answer);
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
        new Z().run();
    }
}
