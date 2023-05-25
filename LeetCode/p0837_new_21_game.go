func new21Game(n int, k int, maxPts int) float64 {
    prob := 1.0 / float64(maxPts)

    dp := make([]float64, n + 1)
    windowSum := 0.0

    dp[0] = 1.0

    for i := 0; i <= n; i++ {
        notUsed := i - maxPts - 1
        if 0 <= notUsed && notUsed < k {
            windowSum -= dp[i - maxPts - 1]   
        }

        if i > 0 {
            dp[i] = windowSum * prob
        }

        if i < k {
            windowSum += dp[i]
        }
    }

    answer := 0.0
    for i := k; i <= n; i++ {
        answer += dp[i]
    }

    return answer
}
