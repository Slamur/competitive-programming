def read_int():
    return int(input())


def read_strings():
    return input().split()


def read_ints():
    return map(int, read_strings())


max_n = 10**6 + 1
dp = list(range(max_n))

for d in range(1, max_n):
    dp[d] = min(dp[d], dp[d - 1] + 1)
    for x in range(2 * d, min((d + 1) * d, max_n), d):
        dp[x] = min(dp[x], dp[d] + 1)

q = read_int()
queries = [read_int() for _ in range(q)]

for n in queries:
    print(dp[n])

