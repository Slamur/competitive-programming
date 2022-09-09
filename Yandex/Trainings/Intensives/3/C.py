def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n = read_int()
a = list(read_ints())

pref = [0] * (n + 1)
for i in range(n):
    delta = 1 if a[i] > 0 else 0
    pref[i + 1] = pref[i] + delta

ans = []

q = read_int()
for _ in range(q):
    left, right = read_ints()
    ans.append(pref[right] - pref[left - 1])

print("\n".join(map(str, ans)))
