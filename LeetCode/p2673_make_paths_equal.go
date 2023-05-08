func minIncrements(n int, costs []int) int {
    path := make([]int, n + 1)
    for i, cost := range costs {
        path[i + 1] = cost
    }

    answer := 0
    for i := n; i > 0; i-- {
        left := i * 2
        if left <= n {
            right := left + 1

            left_path, right_path := path[left], path[right]
            if left_path < right_path {
                left_path, right_path = right_path, left_path
            }

            answer += left_path - right_path
            path[i] += left_path
        }
    }

    return answer
}
