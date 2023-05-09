from threading import Event

class Foo:
    def __init__(self):
        self.e2 = Event()
        self.e3 = Event()


    def first(self, printFirst: 'Callable[[], None]') -> None:
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.e2.set()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.e2.wait()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self.e3.set()


    def third(self, printThird: 'Callable[[], None]') -> None:
        self.e3.wait()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()
