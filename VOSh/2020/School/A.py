def read_ints():
    # return list(map(int, input().split()))
    return [int(i) for i in input().split()]


def read_int():
    return read_ints()[0]


def solve():
    k = read_int()
    n = read_int()

    left = n // k
    right = left + 1

    left_x = left * k
    right_x = right * k

    ans = min(n - left_x, right_x - n)
    print(ans)


solve()
