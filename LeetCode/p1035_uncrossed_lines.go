func max(a, b int) int {
    if a < b {
        return b
    } else {
        return a
    }
}

func maxUncrossedLines(nums1 []int, nums2 []int) int {
    n1, n2 := len(nums1), len(nums2)
    if n1 < n2 {
        nums1, nums2 = nums2, nums1
        n1, n2 = n2, n1
    }

    dp := make([][]int, 2)
    for it := range dp {
        dp[it] = make([]int, n2 + 1)
    }

    for i1, val1 := range nums1 {
        prevDp := dp[i1 % 2]
        curDp := dp[1 - i1 % 2]

        curDp[0] = prevDp[0]
        for i2, val2 := range nums2 {
            curDp[i2 + 1] = max(
                prevDp[i2 + 1],
                curDp[i2],
            )
            
            if val1 == val2 {
                curDp[i2 + 1] = max(
                    curDp[i2 + 1],
                    prevDp[i2] + 1,
                )
            }
        }
    }

    return dp[n1 % 2][n2]
}
