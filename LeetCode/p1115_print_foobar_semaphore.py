from threading import Semaphore

class FooBar:
    def __init__(self, n):
        self.n = n
        self.can_foo = Semaphore(1)
        self.can_bar = Semaphore(0)


    def foo(self, printFoo: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            self.can_foo.acquire()
            # printFoo() outputs "foo". Do not change or remove this line.
            printFoo()
            self.can_bar.release()

    def bar(self, printBar: 'Callable[[], None]') -> None:
        
        for i in range(self.n):
            self.can_bar.acquire()
            # printBar() outputs "bar". Do not change or remove this line.
            printBar()
            self.can_foo.release()
