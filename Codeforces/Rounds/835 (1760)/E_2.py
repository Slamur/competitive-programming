from threading import stack_size

mb = 1024 * 1024
stack_size(128 * mb)


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n = read_int()
    a = list(read_ints())

    def calc():
        ones = 0
        inversions = 0
        for v in a:
            if v == 1:
                ones += 1
            else:
                inversions += ones
                
        return inversions
        
    best = calc()
    
    first_zero = -1
    for i, v in enumerate(a):
        if v == 0:
            first_zero = i
            break
        
    if first_zero != -1:
        a[first_zero] = 1
        best = max(best, calc())
        a[first_zero] = 0
    
    last_one = -1
    for i, v in enumerate(a):
        if v == 1:
            last_one = i
            
    if last_one != -1:
        a[last_one] = 0
        best = max(best, calc())
        a[last_one] = 1
    
    print(best)


tests = read_int()
for test in range(tests):
    solve_test()
