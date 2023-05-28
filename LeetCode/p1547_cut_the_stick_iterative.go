func minCost(size int, cuts []int) int {
    sort.Ints(cuts)
    cuts = append([]int{0}, cuts...)
    cuts = append(cuts, size)

    n := len(cuts) - 1

    inf := size * (n + 1)

    dp := make([][]int, n)
    for start := range dp {
        dp[start] = make([]int, n + 1)
        for end := start; end <= n; end++ {
            dp[start][end] = inf
        }

        dp[start][start + 1] = 0
    }

    for shift := 2; shift <= n; shift++ {
        for end := shift; end <= n; end++ {
            start := end - shift
            length := cuts[end] - cuts[start]
            for mid := start + 1; mid < end; mid++ {
                cost := dp[start][mid] + dp[mid][end] + length
                if dp[start][end] > cost {
                    dp[start][end] = cost
                }
            }
        }
    }

    return dp[0][n]
}
