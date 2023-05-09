from threading import Semaphore

class ZeroEvenOdd:
    def __init__(self, n):
        self.n = n
        
        self.can_zero = Semaphore(1)
        self.can_odd = Semaphore(0)
        self.can_even = Semaphore(0)
        
        
	# printNumber(x) outputs "x", where x is an integer.
    def zero(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n + 1):
            self.can_zero.acquire()
            printNumber(0)
            
            released = self.can_odd if i % 2 == 1 else self.can_even
            released.release()
        

    def even(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(2, self.n + 1, 2):
            self.can_even.acquire()
            printNumber(i)
            self.can_zero.release()
        

    def odd(self, printNumber: 'Callable[[int], None]') -> None:
        for i in range(1, self.n + 1, 2):
            self.can_odd.acquire()
            printNumber(i)
            self.can_zero.release()
