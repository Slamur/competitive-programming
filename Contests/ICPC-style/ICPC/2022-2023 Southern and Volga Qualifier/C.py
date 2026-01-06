def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n, k = read_ints()
s = input()

rev = False

left, right = 0, n - 1
for _ in range(k):
    if s[left] != s[right]:
        rev = not rev
    left += 1
    right -= 1

if rev:
    s = s[::-1]

print(s[left:right + 1])
