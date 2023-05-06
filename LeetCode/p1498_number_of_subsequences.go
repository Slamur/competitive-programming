func numSubseq(nums []int, target int) int {
    n := len(nums)

    sort.Ints(nums)

    usedPows := make([]bool, n)

    for left, right := 0, n - 1; left < n; left++ {
        for ; right >= left && nums[right] + nums[left] > target; right-- {}

        // nums[right] + nums[left] <= target
        if left <= right {
            free := right - left
            usedPows[free] = true
        }
    }

    answer := 0

    mod := 1000 * 1000 * 1000 + 7
    pow := 1
    for _, usedPow := range usedPows {
        if usedPow {
            answer += pow
            if answer >= mod {
                answer -= mod
            }
        }

        pow += pow
        if pow >= mod {
            pow -= mod
        }
    }

    return answer
}
