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

    var calculate func(int, int) int
    calculate = func(start, end int) int {
        if dp[start][end] < inf {
            return dp[start][end]
        }

        length := cuts[end] - cuts[start]
        for mid := start + 1; mid < end; mid++ {
            cost := calculate(start, mid) + calculate(mid, end) + length
            if dp[start][end] > cost {
                dp[start][end] = cost
            }
        }

        return dp[start][end]
    }

    return calculate(0, n)
}
