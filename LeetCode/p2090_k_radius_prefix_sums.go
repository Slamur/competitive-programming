func getAverages(nums []int, k int) []int {
    n := len(nums)
    prefs := make([]int64, n + 1)
    for i, v := range nums {
        prefs[i + 1] = prefs[i] + int64(v)
    }

    ans := make([]int, n)
    for i := range ans {
        ans[i] = -1
    }

    size := 2 * k + 1
    for i := range prefs {
        left := i - k
        right := i + k

        if left > 0 && right < len(prefs) {
            sum := prefs[right] - prefs[left - 1]
            ans[i - 1] = int(sum / int64(size))
        }
    }

    return ans
}
