import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Locale;
import java.util.StringTokenizer;

public class Y {

    private void solve() {
        String id = readLine();

        boolean isCorrect = isCorrect(id);
        yesNo(isCorrect);
    }

    boolean isCorrect(String id) {
        int atIndex = id.indexOf('@');
        if (atIndex < 0) return false;

        String userName = id.substring(0, atIndex);
        if (!isCorrectWord(userName, 16)) return false;

        int slashIndex = id.indexOf('/');

        if (slashIndex < 0) {
            slashIndex = id.length();
        }

        String hostName = id.substring(atIndex + 1, slashIndex);
        if (!isCorrectLength(hostName, 32)) return false;

        if (hostName.startsWith(".")) return false;
        if (hostName.endsWith(".")) return false;

        String[] hostNameParts = hostName.split("[.]");
        for (String hostNamePart : hostNameParts) {
            if (!isCorrectWord(hostNamePart, 16)) return false;
        }

        if (slashIndex < id.length()) {
            String resource = id.substring(slashIndex + 1);
            return isCorrectWord(resource, 16);
        } else {
            return true;
        }
    }

    boolean isCorrectLength(String s, int maxLength) {
        return !s.isEmpty() && s.length() <= maxLength;
    }

    boolean isCorrectWord(String part, int maxLength) {
        if (!isCorrectLength(part, maxLength)) return false;

        for (char ch : part.toCharArray()) {
            if (!isCorrectCharacter(ch)) return false;
        }

        return true;
    }

    boolean isCorrectCharacter(char ch) {
        if (Character.isLetterOrDigit(ch)) return true;
        return '_' == ch;
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
        new Y().run();
    }
}
