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

    neg_inf = min(a) - 1
    
    max_score = max(a)
    max_index = a.index(max_score)
    
    a[max_index] = neg_inf
    second_max_score = max(a)
    a[max_index] = max_score
    
    ans = [v - max_score for v in a]
    ans[max_index] = max_score - second_max_score

    print(' '.join(map(str, ans)))


tests = read_int()
for test in range(tests):
    solve_test()
