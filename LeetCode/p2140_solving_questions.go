func mostPoints(questions [][]int) int64 {
    n := len(questions)
    
    dp := make([]int64, n + 1)
    dp[n] = 0

    for i := n - 1; i >= 0; i-- {
        res := dp[i + 1]
        
        points, delay := questions[i][0], questions[i][1]

        answered := int64(points)

        first := i + delay + 1
        if first <= n {
            answered += dp[first]
        }
        
        if res < answered {
            res = answered
        }

        dp[i] = res
    }

    return dp[0]
}
