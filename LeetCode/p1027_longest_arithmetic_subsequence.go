import "fmt"

func longestArithSeqLength(nums []int) int {
    n := len(nums)

    maxDelta := 500

    dp := make([][]int, n)
    for i := range dp {
        dp[i] = make([]int, maxDelta * 2 + 1)
    }

    ans := 0
    for i, num := range nums {
        for last := 0; last < i; last++ {
            delta := num - nums[last] + maxDelta
            if dp[i][delta] < dp[last][delta] + 1 {
                dp[i][delta] = dp[last][delta] + 1
            }

            if ans < dp[i][delta] {
                ans = dp[i][delta]
            }
        }
    }

    return ans + 1
}
