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
    a.insert(0, neg_inf)

    pref_max = [neg_inf] * (n + 1)
    for i in range(1, n + 1):
        pref_max[i] = max(pref_max[i - 1], a[i])

    suff_max = [neg_inf] * (n + 2)
    for i in range(n, 0, -1):
        suff_max[i] = max(suff_max[i + 1], a[i])

    ans = [
        a[i] - max(pref_max[i - 1], suff_max[i + 1])
        for i in range(1, n + 1)
    ]

    print(' '.join(map(str, ans)))


tests = read_int()
for test in range(tests):
    solve_test()
