func minCost(nums []int, costs []int) int64 {
    n := len(nums)

    values := make([][2]int64, n)
    for i, cost := range costs {
        values[i] = [2]int64{
            int64(nums[i]),
            int64(cost),
        }
    }

    sort.Slice(values, func(i, j int) bool {
        return values[i][0] < values[j][0]
    })

    prefs := make([][2]int64, n + 1)
    suffs := make([][2]int64, n + 2)

    prefs[0] = [2]int64{
        0,
        0,
    }

    for i, numCost := range values {
        cost := numCost[1]
        prefs[i + 1] = [2]int64{
            prefs[i][0] + int64(cost),
            prefs[i][1] + int64(cost) * int64(numCost[0]),
        }
    }

    suffs[n + 1] = [2]int64{
        0,
        0,
    }

    for i := n - 1; i >= 0; i-- {
        cost := values[i][1]

        suffs[i + 1] = [2]int64{
            suffs[i + 2][0] + int64(cost),
            suffs[i + 2][1] + int64(cost) * int64(values[i][0]),
        }
    }

    ans := int64(math.MaxInt64)

    for i, numCost := range values {
        num := numCost[0]

        left := int64(num) * prefs[i][0] - prefs[i][1]
        right := suffs[i + 2][1] - int64(num) * suffs[i + 2][0]

        if ans > left + right {
            ans = left + right
        }
    }

    return ans
}
