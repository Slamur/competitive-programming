from threading import Barrier

class Foo:
    def __init__(self):
        self.b2 = Barrier(2)
        self.b3 = Barrier(2)


    def first(self, printFirst: 'Callable[[], None]') -> None:
        # printFirst() outputs "first". Do not change or remove this line.
        printFirst()
        self.b2.wait()


    def second(self, printSecond: 'Callable[[], None]') -> None:
        self.b2.wait()
        # printSecond() outputs "second". Do not change or remove this line.
        printSecond()
        self.b3.wait()


    def third(self, printThird: 'Callable[[], None]') -> None:
        self.b3.wait()
        # printThird() outputs "third". Do not change or remove this line.
        printThird()
