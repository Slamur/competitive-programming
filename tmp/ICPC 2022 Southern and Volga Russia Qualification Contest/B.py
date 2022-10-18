def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


t = read_int()
for _ in range(t):
    n = read_int()

    p = [0] * n
    p[0] = 1
    for i in range(1, n):
        p[i] = n - i + 1

    print(*p)
