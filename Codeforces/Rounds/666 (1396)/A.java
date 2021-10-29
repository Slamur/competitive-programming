import java.io.*;
import java.util.*;
import java.util.stream.*;
import java.awt.Point;

public class A {

	static class Operation {
		int start, end;
		List<Long> values;
		
		Operation(int start, int end, List<Long> values) {
			this.start = start;
			this.end = end;
			this.values = values;
		}
	}

    private void solve() {
        int n = readInt();
		int[] a = readIntArray(n);
		
		List<Operation> answer = getAnswer(n, a);
		answer.forEach(operation -> {
			out.println(
				(operation.start + 1) + " " + operation.end
			);
			for (long value : operation.values) {
				out.print(value + " ");
			}
			out.println();
		});
    }
	
	private List<Operation> getAnswer(int n, int[] a) {
		if (1 == n) {
			return List.of(
				new Operation(0, 1, List.of((long)-a[0])),
				new Operation(0, 1, List.of(0L)),
				new Operation(0, 1, List.of(0L))
			);
		}
		
		int last = a[n - 1];
		a[n - 1] = 0;
		
		return List.of(
			new Operation(0, n - 1,
				IntStream.range(0, n - 1)
					.map(index -> a[index])
					.mapToLong(value -> (n - 1) * (long)value)
					.boxed()
					.collect(Collectors.toList())
			),
			new Operation(n - 1, n,
				List.of(-(long)last)
			),
			new Operation(0, n,
				Arrays.stream(a)
					.mapToLong(value -> -n * (long)value)
					.boxed()
					.collect(Collectors.toList())
			)
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
        new A().run();
    }
}
