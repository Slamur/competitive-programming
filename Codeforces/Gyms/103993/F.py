def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n = read_int()
covered = list(ch == '1' for ch in input())
covered.insert(0, False)

costs = list(read_ints())
costs.insert(0, 0)

COVERED = 1
NOT_COVERED = 0

neg_inf = -10**18
dp = [[neg_inf] * (n + 1) for _ in range(2)]

dp[NOT_COVERED][0] = 0
for i in range(1, n + 1):
    if covered[i]:
        dp[NOT_COVERED][i] = max(
            dp[NOT_COVERED][i],
            dp[NOT_COVERED][i - 1] + costs[i - 1]
        )

        dp[COVERED][i] = max(
            dp[COVERED][i],
            dp[COVERED][i - 1] + costs[i]
        )

        dp[COVERED][i] = max(
            dp[COVERED][i],
            dp[NOT_COVERED][i - 1] + costs[i]
        )
    else:
        dp[NOT_COVERED][i] = max(
            dp[NOT_COVERED][i],
            dp[NOT_COVERED][i - 1]
        )

        dp[NOT_COVERED][i] = max(
            dp[NOT_COVERED][i],
            dp[COVERED][i - 1]
        )

ans = max(dp[NOT_COVERED][n], dp[COVERED][n])
print(ans)
