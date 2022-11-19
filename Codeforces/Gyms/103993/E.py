def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n, d = read_ints()
a = list(read_ints())

for start in range(d):
    values = []
    for i in range(start, n, d):
        values.append(a[i])
    values.sort()

    j = 0
    for i in range(start, n, d):
        a[i] = values[j]
        j += 1

can = a == sorted(a)
print('YES' if can else 'NO')
