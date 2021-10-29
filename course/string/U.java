import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class U {

    private void solve() {
        int n = readInt();
        String[] words = new String[n];
        for (int i = 0; i < n; ++i) {
            words[i] = readString();
        }

        String text = readString();
        char luckyCh = readString().charAt(0);

        String answer = getAnswer(text, words, luckyCh);
        out.println(answer);
    }

    String getAnswer(String text, String[] words, char luckyCh) {
        int n = text.length();
        boolean[] covered = new boolean[n];

        for (String word : words) {
            word = word.toLowerCase();

            for (int i = 0, len = word.length(); i + len <= n; ++i) {
                String textSegment = text.substring(i, i + len).toLowerCase();
                if (textSegment.equals(word)) {
                    for (int j = 0; j < len; ++j) {
                        covered[i + j] = true;
                    }
                }
            }
        }

        char otherCh = ('a' == luckyCh) ? 'b' : 'a';

        char[] answer = text.toCharArray();

        for (int i = 0; i < n; ++i) {
            if (!covered[i]) continue;

            char ch = answer[i];
            boolean isLucky = Character.toLowerCase(ch) == luckyCh;

            char replacedCh = isLucky ? otherCh : luckyCh;
            if (Character.isUpperCase(ch)) replacedCh = Character.toUpperCase(replacedCh);

            answer[i] = replacedCh;
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
        new U().run();
    }
}
