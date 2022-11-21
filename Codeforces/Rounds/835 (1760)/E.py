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

    pref_ones = [0] * (n + 1)
    for i in range(n):
        pref_ones[i + 1] = pref_ones[i] + a[i]

    total = 0
    for i in range(n):
        if a[i] == 0:
            total += pref_ones[i]

    def get_01(left, right):
        cnt_1 = pref_ones[right] - pref_ones[left]
        cnt_0 = (right - left) - cnt_1
        return cnt_0, cnt_1

    best = total
    for i in range(n):
        p0, p1 = get_01(0, i)
        s0, s1 = get_01(i + 1, n)

        cur = total

        if a[i] == 0:
            cur -= p1
            cur += s0
        else:
            cur += p1
            cur -= s0

        best = max(best, cur)

    print(best)


tests = read_int()
for test in range(tests):
    solve_test()
