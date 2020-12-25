import java.awt.Point;
import java.io.*;
import java.util.*;

public class __Solution {

    public static void main(String[] args) {
        new Solution().run();
    }

    static class Solution {
        private void read(SolutionReader in) {

        }

        private void process() {

        }

        private void print(SolutionWriter out) {

        }

        private static final boolean FAST_IO = false;

        private static SolutionReader createReader() {
            return (FAST_IO ? new FastReader() : new ScannerReader());
        }

        private static SolutionWriter createWriter() {
            return new SolutionPrintWriter();
        }

        void run() {
            read();
            process();
            print();
        }

        private boolean consoleIO = false;

        private SolutionReader initReader() {
            SolutionReader reader = createReader();

            try {
                reader.setInput("input.txt");
            } catch (FileNotFoundException e) {
                reader.setInput(System.in);
                consoleIO = true;
            }

            return reader;
        }

        private void read() {
            try (SolutionReader in = initReader()){
                read(in);
            } catch (IOException ignored) {

            }
        }

        private SolutionWriter initWriter() {
            SolutionWriter writer = createWriter();

            try {
                if (!consoleIO) {
                    writer.setOutput("output.txt");
                }
            } catch (IOException e) {
                consoleIO = true;
            }

            if (consoleIO) {
                writer.setOutput(System.out);
            }

            return writer;
        }

        private void print() {
            try (SolutionWriter out = initWriter()) {
                print(out);
            } catch (IOException ignored) {

            }
        }
    }

    static class Utils {
        static List<Integer> order(int size) {
            List<Integer> order = new ArrayList<>();
            for (int i = 0; i < size; ++i) order.add(i);
            return order;
        }

        static int[] castInt(List<Integer> list) {
            int[] array = new int[list.size()];
            for (int i = 0; i < array.length; ++i) {
                array[i] = list.get(i);
            }
            return array;
        }

        static int getBit(int mask, int bit) {
            return ((mask >> bit) & 1);
        }
    }

    interface SolutionReader extends Closeable {

        void setInput(InputStream input);
        void setInput(FileReader input);
        default void setInput(String fileName) throws FileNotFoundException {
            setInput(new FileReader(fileName));
        }

        String readLine();
        String readString();

        int readInt();
        default int[] readIntArray(int n) {
            int[] a = new int[n];
            for (int i = 0; i < n; ++i) {
                a[i] = readInt();
            }
            return a;
        }

        default int[] readIntArrayWithDecrease(int n) {
            int[] a = readIntArray(n);
            for (int i = 0; i < n; ++i) a[i]--;
            return a;
        }

        long readLong();
        default long[] readLongArray(int n) {
            long[] a = new long[n];
            for (int i = 0; i < n; ++i) {
                a[i] = readLong();
            }
            return a;
        }
    }

    static class ScannerReader implements SolutionReader {

        private Scanner in;

        @Override
        public void setInput(FileReader input) {
            this.in = new Scanner(input);
        }

        @Override
        public void setInput(InputStream input) {
            this.in = new Scanner(input);
        }

        @Override
        public String readLine() {
            String result = in.nextLine();
            if (result != null && result.isEmpty()) result = in.nextLine();
            return result;
        }

        @Override
        public String readString() {
            return in.next();
        }

        @Override
        public int readInt() {
            return in.nextInt();
        }

        @Override
        public long readLong() {
            return in.nextLong();
        }

        @Override
        public void close() {
            in.close();
        }
    }

    static class FastReader implements SolutionReader {

        private BufferedReader in;
        private StringTokenizer tok;

        private void initTokenizer() {
            this.tok = new StringTokenizer("");
        }

        @Override
        public void setInput(FileReader input) {
            this.in = new BufferedReader(input);
            initTokenizer();
        }

        @Override
        public void setInput(InputStream input) {
            this.in = new BufferedReader(new InputStreamReader(input));
            initTokenizer();
        }

        @Override
        public String readLine() {
            try {
                return in.readLine();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        @Override
        public String readString() {
            while (!tok.hasMoreTokens()) {
                String nextLine = readLine();
                if (nextLine == null) return null;
                tok = new StringTokenizer(nextLine);
            }

            return tok.nextToken();
        }

        @Override
        public int readInt() {
            return Integer.parseInt(readString());
        }

        @Override
        public long readLong() {
            return Long.parseLong(readString());
        }

        @Override
        public void close() throws IOException {
            in.close();
        }
    }

    interface SolutionWriter extends Closeable {

        void setOutput(PrintStream out);
        void setOutput(FileWriter out);

        default void setOutput(String fileName) throws IOException {
            setOutput(new FileWriter(fileName));
        }

        SolutionWriter println();

        SolutionWriter print(String line);

        default SolutionWriter print(char character) { return print("" + character); }
        default SolutionWriter printSpace() {
            return print(" ");
        }

        SolutionWriter print(int value);
        SolutionWriter print(long value);
        SolutionWriter print(double value);

        default SolutionWriter printAll(int... values) {
            for (int value : values) {
                print(value).printSpace();
            }
            return this;
        }

        default SolutionWriter printAll(Iterable<Integer> values) {
            for (int value : values) {
                print(value).printSpace();
            }
            return this;
        }

        default SolutionWriter printIndexes(int... indexes) {
            for (int index : indexes) {
                print(index + 1).printSpace();
            }
            return this;
        }

        default SolutionWriter printAllSeparated(int... values) {
            for (int value : values) {
                print(value).println();
            }
            return this;
        }

        default SolutionWriter printAllSeparated(long... values) {
            for (long value : values) {
                print(value).println();
            }
            return this;
        }

        default SolutionWriter printPointsSeparated(Point[] points) {
            for (Point point : points) {
                printAll(point.x, point.y).println();
            }
            return this;
        }

        default SolutionWriter printAll(long... values) {
            for (long value : values) {
                print(value).printSpace();
            }
            return this;
        }

        default SolutionWriter printAll(double... values) {
            for (double value : values) {
                print(value).printSpace();
            }
            return this;
        }
    }

    static class SolutionPrintWriter implements SolutionWriter {

        private PrintWriter out;

        @Override
        public void setOutput(PrintStream out) {
            this.out = new PrintWriter(out);
        }

        @Override
        public void setOutput(FileWriter out) {
            this.out = new PrintWriter(out);
        }

        @Override
        public SolutionWriter println() {
            out.println();
            return this;
        }

        @Override
        public SolutionWriter print(String line) {
            out.print(line);
            return this;
        }

        @Override
        public SolutionWriter print(int value) {
            out.print(value);
            return this;
        }

        @Override
        public SolutionWriter print(long value) {
            out.print(value);
            return this;
        }

        @Override
        public SolutionWriter print(double value) {
            out.printf(Locale.US, "%.12f", value);
            return this;
        }

        @Override
        public void close() {
            out.close();
        }
    }
}