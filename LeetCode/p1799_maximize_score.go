func gcd(a, b int) int {
    for ; a != 0; a, b = b % a, a {}
    return b
}

func getBit(mask, bit int) bool {
    return ((mask >> bit) & 1) != 0
}

func maxScore(nums []int) int {
    n := len(nums)

    g := make([][]int, n)
    for i, vi := range nums {
        g[i] = make([]int, n)
        for j, vj := range nums {
            g[i][j] = gcd(vi, vj)
        }
    }

    size := 1 << n

    dp := make([]int, size)

    for mask := 1; mask < size; mask++ {
        dp[mask] = -1

        bitCount := bits.OnesCount(uint(mask))
        if bitCount % 2 == 1 {
            continue
        }

        res := dp[mask]

        iteration := bitCount / 2
        for first := 0; first < n; first++ {
            if !getBit(mask, first) {
                continue
            }

            maskWithoutFirst := mask ^ (1 << first)
            for second := first + 1; second < n; second++ {
                if !getBit(mask, second) {
                    continue
                }

                prevMask := maskWithoutFirst ^ (1 << second)
                
                firstSecondRes := dp[prevMask] + g[first][second] * iteration
                if res < firstSecondRes {
                    res = firstSecondRes
                }
            }
        }

        dp[mask] = res
    }

    return dp[size - 1]
}
