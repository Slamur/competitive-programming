def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


a = list(read_ints())
a = list(set(a))
a = sorted(a)

if len(a) == 1:
    print(a[0])
else:
    n = len(a)
    deltas = []
    for i in range(1, n):
        deltas.append(a[i] - a[0])

    def gcd(a, b):
        return b if a == 0 else gcd(b % a, a)

    g = 0
    for delta in deltas:
        g = gcd(g, delta)

    a_1 = a[0]
    a_last = a[-1]
    size = (a_last - a_1) // g + 1

    s = (a_1 + a_last) * size // 2
    print(s)
