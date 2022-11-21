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

    inf = max(a) + 1

    a.insert(0, inf)
    a.append(inf)

    min_value = min(a)
    min_index = a.index(min_value)

    pref_decreasing = True
    for i in range(min_index):
        pref_decreasing &= a[i] >= a[i + 1]

    suff_increasing = True
    for i in range(min_index, len(a) - 1):
        suff_increasing &= a[i] <= a[i + 1]

    good = pref_decreasing and suff_increasing
    print('YES' if good else 'NO')


tests = read_int()
for test in range(tests):
    solve_test()
