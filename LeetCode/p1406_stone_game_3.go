func signum(x int) int {
    if x < 0 { return -1 }
    if x > 0 { return 1 }
    return 0
}

func stoneGameIII(stoneValue []int) string {
    n := len(stoneValue)

    maxTaken := 3
    dp := make([]int, maxTaken + 1)

    inf := math.MaxInt

    suffSum := 0

    for i := n - 1; i >= 0; i-- {
        suffSum += stoneValue[i]

        bestResult := inf
        for taken := 1; taken <= maxTaken && i + taken <= n; taken++ {
            result := dp[(i + taken) % maxTaken]
            if bestResult > result {
                bestResult = result
            }
        }

        dp[i % maxTaken] = suffSum - bestResult
    }

    sign := signum(2 * dp[0] - suffSum)

    // sign > 0 -> alice
    // sign < 0 -> bob
    // sign = 0 - tie

    return []string{
        "Bob",
        "Tie",
        "Alice",
    }[sign + 1]
}
