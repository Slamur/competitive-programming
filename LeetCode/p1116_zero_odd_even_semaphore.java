import java.util.concurrent.Semaphore;

class ZeroEvenOdd {
    private int n;

    Semaphore canZero, canOdd, canEven;
    
    public ZeroEvenOdd(int n) {
        this.n = n;

        this.canZero = new Semaphore(1);
        this.canOdd = new Semaphore(0);
        this.canEven = new Semaphore(0);
    }

    // printNumber.accept(x) outputs "x", where x is an integer.
    public void zero(IntConsumer printNumber) throws InterruptedException {
        for (int i = 1; i <= n; ++i) {
            canZero.acquire();
            printNumber.accept(0);

            (i % 2 == 1 ? canOdd : canEven).release();
        }
    }

    public void even(IntConsumer printNumber) throws InterruptedException {
        for (int i = 2; i <= n; i += 2) {
            canEven.acquire();
            printNumber.accept(i);
            canZero.release();
        }
    }

    public void odd(IntConsumer printNumber) throws InterruptedException {
        for (int i = 1; i <= n; i += 2) {
            canOdd.acquire();
            printNumber.accept(i);
            canZero.release();
        }
    }
}
