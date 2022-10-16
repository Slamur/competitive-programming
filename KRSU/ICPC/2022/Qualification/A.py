def read_int():
    return int(input())


n = read_int()
k = read_int()

ans = 0
while n > 0:
    n //= k
    ans += 1

print(ans)
