func to_ids(target, source *[]int) int {
    t_len := len(*target)
    s_len := len(*source)

    values := make([]int, 0, t_len + s_len)

    for _, val := range (*target) {
        values = append(values, val)
    }
    for _, val := range (*source) {
        values = append(values, val)
    }

    sort.Ints(values)
    
    for i, val := range (*target) {
        (*target)[i] = sort.SearchInts(values, val)
    }

    for i, val := range (*source) {
        (*source)[i] = sort.SearchInts(values, val)
    }

    return len(values)
}

func makeArrayIncreasing(target []int, source []int) int {
    size := to_ids(&target, &source)

    available := make([]bool, size)
    for _, val := range source {
        available[val] = true
    }

    dp := [2][]int {
        make([]int, size + 1),
        make([]int, size + 1),
    }

    n := len(target)
    no_ans := n + 1

    dp[0][0] = 0
    for id := 1; id <= size; id++ {
        dp[0][id] = dp[0][id - 1]
    }

    for i, target_id := range target {
        prev, cur := i % 2, 1 - i % 2

        dp[cur][0] = no_ans
        for last_id := 0; last_id < size; last_id++ {
            cost := no_ans
            if last_id == target_id {
                cost = 0
            } else if available[last_id] {
                cost = 1
            }

            best := dp[cur][last_id]

            if best > dp[prev][last_id] + cost {
                best = dp[prev][last_id] + cost
            }

            dp[cur][last_id + 1] = best
        }
    }

    ans := dp[n % 2][size]

    if no_ans == ans {
        return -1
    }

    return ans
}
