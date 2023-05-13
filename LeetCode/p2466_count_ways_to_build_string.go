func countGoodStrings(low int, high int, zero int, one int) int {
    mod := 1000 * 1000 * 1000 + 7

    dp := make([]int, high + 1)
    dp[0] = 1

    for i := 1; i <= high; i++ {
        res := 0
        if i >= zero {
            res += dp[i - zero]
            if res >= mod {
                res -= mod
            }
        }

        if i >= one {
            res += dp[i - one]
            if res >= mod {
                res -= mod
            }
        }

        dp[i] = res
    }

    ans := 0
    for i := low; i <= high; i++ {
        ans += dp[i]
        if ans >= mod {
            ans -= mod
        }
    }

    return ans
}
