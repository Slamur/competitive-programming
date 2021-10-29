import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class X {

    private void solve() {
        String a = readString();
        String b = readString();
        String c = readString();

        String answer = getAnswer(a, b, c);
        out.println(answer);
    }

    String getAnswer(String a, String b, String c) {
        int[] aCounts = getCounts(a);
        int[] bCounts = getCounts(b);
        int[] cCounts = getCounts(c);

        int bestB = 0, bestC = 0;

        int maxB = getMaxTimes(aCounts, bCounts);
        int[] aNoBCounts = new int[1 << 8];

        for (int bTimes = 0; bTimes <= maxB; ++bTimes) {
            for (char ch = 'a'; ch <= 'z'; ++ch) {
                aNoBCounts[ch] = aCounts[ch] - bCounts[ch] * bTimes;
            }

            int cTimes = getMaxTimes(aNoBCounts, cCounts);
            if (cTimes < 0) continue;

            if (bestB + bestC < bTimes + cTimes) {
                bestB = bTimes;
                bestC = cTimes;
            }
        }

        StringBuilder answer = new StringBuilder();

        answer.append(b.repeat(bestB));
        answer.append(c.repeat(bestC));

        for (char ch = 'a'; ch <= 'z'; ++ch) {
            int notUsed = aCounts[ch] - bestB * bCounts[ch] - bestC * cCounts[ch];
            String chString = "" + ch;
            answer.append(chString.repeat(notUsed));
        }

        return answer.toString();
    }

    int[] getCounts(String s) {
        int[] counts = new int[1 << 8];
        for (char ch : s.toCharArray()) {
            counts[ch]++;
        }
        return counts;
    }

    int getMaxTimes(int[] sourceCounts, int[] targetCounts) {
        int maxTimes = Integer.MAX_VALUE;

        for (char ch = 'a'; ch <= 'z'; ++ch) {
            int sourceCount = sourceCounts[ch];
            int targetCount = targetCounts[ch];

            if (sourceCount < 0) return -1;
            if (targetCount == 0) continue;

            maxTimes = Math.min(maxTimes, sourceCount / targetCount);
        }

        return maxTimes;
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
        new X().run();
    }
}
