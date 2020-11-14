import java.io.PrintWriter;
import java.util.*;

import static java.lang.Math.abs;


public class __Generator {

    private static String[] args;

    @SuppressWarnings("unused")
    private static String readString(int i) { return (i < args.length ? args[i] : null); }

    @SuppressWarnings("unused")
    private static int readInt(int i) {
        return Integer.parseInt(args[i]);
    }

    private static long readLong(int i) {
        return Long.parseLong(args[i]);
    }

    @SuppressWarnings("unused")
    private static double readDouble(int i) {
        return Double.parseDouble(args[i]);
    }

    private static Random rnd;

    private static void setSeed(long seed) {
        rnd = new Random(seed);
    }

    @SuppressWarnings("unused")
    private static long nextLong(long min, long max) {
        return abs(rnd.nextLong()) % (max - min + 1) + min;
    }

    private static int nextInt(int min, int max) {
        return rnd.nextInt(max - min + 1) + min;
    }

    private static int[] nextInts(int size, int min, int max) {
        int[] array = new int[size];
        for (int i = 0; i < size; ++i) {
            array[i] = nextInt(min, max);
        }

        return array;
    }

    public static void main(String[] args) {
        __Generator.args = args;

        long seed = readLong(0);
        setSeed(seed);

        // read parameters

        // generating

        // output
        PrintWriter out = new PrintWriter(System.out);

        out.close();
    }

    @SuppressWarnings("unused")
    private static void println(PrintWriter out, int... values) {
        print(out, true, values);
    }

    private static void print(PrintWriter out, boolean println, int... values) {
        boolean first = true;
        for (int value : values) {
            if (!first) out.print(" ");
            first = false;
            out.print(value);
        }

        if (println) out.println();
    }

    /**
     * Generates list with keys 0..<n
     * @param n - exclusive limit of sequence
     */
    private static List<Integer> order(int n) {
        List<Integer> sequence = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            sequence.add(i);
        }

        return sequence;
    }

    @SuppressWarnings("unused")
    private static <T> List<T> shuffled(List<T> list) {
        Collections.shuffle(list, rnd);
        return list;
    }

    @SuppressWarnings("unused")
    private static int[] castInt(List<Integer> list) {
        int[] array = new int[list.size()];
        for (int i = 0; i < array.length; ++i) {
            array[i] = list.get(i);
        }

        return array;
    }

    private static int getBit(int mask, int bit) {
        return (mask >> bit) & 1;
    }

    private static boolean checkBit(int mask, int bit) {
        return getBit(mask, bit) == 1;
    }


    private static int[] nextUniqueInts(int size, int min, int max) {
        if (max - min <= 1000 * 1000) {
            return nextUniqueIntsRandomSort(size, min, max);
        } else if (size * 100 < (max - min)) {
            return nextUniqueIntsWhileContains(size, min, max);
        } else {
            return nextUniqueIntsKthZero(size, min, max);
        }
    }

    private static int[] nextUniqueIntsRandomSort(int size, int min, int max) {
        class Pair implements Comparable<Pair> {
            double value;
            int index;

            public Pair(double value, int index) {
                this.value = value;
                this.index = index;
            }

            @Override
            public int compareTo(Pair other) {
                return Double.compare(value, other.value);
            }
        }

        Pair[] pairs = new Pair[max - min + 1];
        for (int i = 0; i < pairs.length; ++i) {
            pairs[i] = new Pair(rnd.nextDouble(), i);
        }

        Arrays.sort(pairs);

        int[] values = new int[size];
        for (int i = 0; i < size; ++i) {
            values[i] = pairs[i].index + min;
        }

        return values;
    }

    private static int[] nextUniqueIntsWhileContains(int size, int min, int max) {
        Set<Integer> used = new HashSet<>();

        int[] values = new int[size];
        for (int i = 0; i < size; ++i) {
            while (true) {
                int value = nextInt(min, max);
                if (used.add(value)) {
                    values[i] = value;
                    break;
                }
            }
        }

        return values;
    }

    private static int[] nextUniqueIntsKthZero(int size, int min, int max) {
        int[] array = new int[size];

        int count = max - min + 1;

        PersistentSegmentTree taken = new PersistentSegmentTree(32);
        for (int index = 0; index < size; ++index) {
            int next = rnd.nextInt(count);
            long value = taken.getKth(next);

            array[index] = (int)(value + min);
            taken.remove(value);
            --count;
        }

        return array;
    }

    private static int[] nextPermutation(int size) {
        return castInt(shuffled(order(size)));
    }

    interface GeneratorType {
        int RANDOM = 0, PERMUTATION = 1;
    }

    @SuppressWarnings("unused")
    private static int[] generateArray(int size, int type) {
        switch (type) {
            case GeneratorType.PERMUTATION:
                return nextPermutation(size);
            case GeneratorType.RANDOM:
            default:
                return nextInts(size, 1, size);
        }
    }

    private static void fillArray(int[] target, int start, int end, int[] source) {
        System.arraycopy(source, 0, target, start, end - start);
    }

    interface OrderType {
        int NONE = 0, SORT = ~1, REVERSE = ~2, SHUFFLE = ~4;
    }

    private static boolean containsMask(int type, int mask) {
        return (type & mask) == type;
    }

    @SuppressWarnings("unused")
    private static void orderArray(int[] array, int type) {
        if (type == OrderType.NONE) return;

        if (containsMask(type, OrderType.SORT)) {
            Arrays.sort(array);
        }

        if (containsMask(type, OrderType.REVERSE)) {
            for (int i = 0, j = array.length - 1; i < j; ++i, --j) {
                swap(array, i, j);
            }
        }

        if (containsMask(type, OrderType.SHUFFLE)) {
            List<Integer> values = new ArrayList<>();
            for (int value : array) values.add(value);
            Collections.shuffle(values, rnd);
            for (int i = 0; i < array.length; ++i) {
                array[i] = values.get(i);
            }
        }
    }

    @SuppressWarnings("unused")
    private static void swapPositions(int[] array, int swapsCount) {
        for (int i = 0; i < swapsCount; ++i) {
            int first = rnd.nextInt(array.length);
            int second = rnd.nextInt(array.length);

            swap(array, first, second);
        }
    }

    private static void swap(int[] array, int first, int second) {
        int tmp = array[first];
        array[first] = array[second];
        array[second] = tmp;
    }

    private static class PersistentSegmentTree {

        private static class Node {

            Node left, right;

            int level;
            long sum;

            Node(int level) {
                this.level = level;
                sum = Math.max(0, (1L << level));
            }

            Node getLeft() {
                if (null == left) left = new Node(level - 1);
                return left;
            }

            Node getRight() {
                if (null == right) right = new Node(level - 1);
                return right;
            }

            void update() {
                this.sum = getLeft().sum + getRight().sum;
            }
        }

        long size;
        Node root;

        PersistentSegmentTree(int levels) {
            this.size = (1L << levels);
            this.root = new Node(levels);
        }

        long index;
        void remove(long index) {
            this.index = index;

            removeTree(root, 0, size);
        }

        void removeTree(Node node, long left, long right) {
            if (left + 1 == right) {
                node.sum = 0;
            } else {
                long mid = (left + right) >> 1;
                if (index < mid) removeTree(node.getLeft(), left, mid);
                else removeTree(node.getRight(), mid, right);

                node.update();
            }
        }

        long size() {
            return root.sum;
        }

        long result;
        long getKth(long index) {
            this.index = index;

            result = -1;
            getTree(root, 0, size);

            return result;
        }

        void getTree(Node node, long left, long right) {
            if (left + 1 == right) {
                result = left;
            } else {
                long mid = (left + right) >> 1;

                if (index < node.getLeft().sum) getTree(node.getLeft(), left, mid);
                else {
                    index -= node.getLeft().sum;
                    getTree(node.getRight(), mid, right);
                }
            }
        }
    }
}