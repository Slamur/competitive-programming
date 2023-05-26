type Solver struct {
    n           int
    suffSums    []int 
    dp          [][]int
}

func createSolver(piles []int) *Solver {
    n := len(piles)

    suffSums := make([]int, n + 1)
    for i := n - 1; i >= 0; i-- {
        suffSums[i] = suffSums[i + 1] + piles[i]
    }

    dp := make([][]int, n + 1)
    for i := range dp {
        dp[i] = make([]int, n + 1)
        for j := range dp[i] {
            dp[i][j] = -1
        }
    }

    return &Solver {
        n: n,
        suffSums: suffSums,
        dp: dp,
    }
}

func max(a, b int) int {
    if a > b {
        return a
    }
    return b
}

func (solver *Solver) calculate(start, m int) (ans int) {
    if start >= solver.n {
        return 0
    }

    ans = solver.dp[start][m]
    if ans >= 0 {
        return ans
    }

    fullSuffix := solver.suffSums[start]
    for taken := 1; taken <= 2 * m; taken++ {
        ans = max(
            ans,
            fullSuffix - solver.calculate(start + taken, max(taken, m)),
        )
    }

    solver.dp[start][m] = ans
    return ans
}

func stoneGameII(piles []int) int {
    solver := createSolver(piles)
    return solver.calculate(0, 1)
}
