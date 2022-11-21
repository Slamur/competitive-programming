from threading import stack_size

mb = 1024 * 1024
stack_size(128 * mb)


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n = read_int()
    text = input()
    
    max_letter = max(text)
    ans = ord(max_letter) - ord('a') + 1
    print(ans)


tests = read_int()
for test in range(tests):
    solve_test()
