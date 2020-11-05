def read_ints():
    # return list(map(int, input().split()))
    return [int(i) for i in input().split()]


def read_int():
    return read_ints()[0]


def solve():
    n = read_int()
    a = [read_int() for _ in range(n)]

    pref_sums = [0] * (n + 1)
    for i in range(n):
        pref_sums[i + 1] = pref_sums[i] + a[i]

    can_rights = [True] * n
    for i in range(n - 2, -1, -1):
        can_rights[i] = (pref_sums[i + 1] > a[i + 1]) and can_rights[i + 1]

    min_value = a[0]
    min_count = 0
    for value in a:
        if value == min_value:
            min_count += 1

    can = [False] * n
    for i in range(n):
        cant_left = (a[i] == min_value and min_count > 1)
        can_left = not cant_left

        can_right = can_rights[i]

        can[i] = can_left and can_right

    for ans in can:
        print(1 if ans else 0)


solve()
