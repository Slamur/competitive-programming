def read_ints():
    return map(int, input().split())


n, m, x, y = read_ints()

rainbow_size = 7
d = (x - 1 + y - 1) % rainbow_size

print(d + 1)

