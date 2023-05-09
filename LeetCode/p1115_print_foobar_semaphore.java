import java.util.concurrent.Semaphore;

class FooBar {
    private int n;

    Semaphore canFoo, canBar;

    public FooBar(int n) {
        this.n = n;
        this.canFoo = new Semaphore(1);
        this.canBar = new Semaphore(0);
    }

    public void foo(Runnable printFoo) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            canFoo.acquire();
        	// printFoo.run() outputs "foo". Do not change or remove this line.
        	printFoo.run();
            canBar.release();
        }
    }

    public void bar(Runnable printBar) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            canBar.acquire();
            // printBar.run() outputs "bar". Do not change or remove this line.
        	printBar.run();
            canFoo.release();
        }
    }
}
