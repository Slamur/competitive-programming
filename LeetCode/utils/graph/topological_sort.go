func topologicalSort(graph [][]int) (order []int) {
    n := len(graph)

    order = make([]int, 0, n)
    used := make([]bool, n)

    var topologicalSortDfs func(int)
    topologicalSortDfs = func(v int) {
        if used[v] {
            return
        }

        used[v] = true

        for _, to := range graph[v] {
            topologicalSortDfs(to)
        }

        order = append(order, v)
    }

    for v := range graph {
        topologicalSortDfs(v)
    }

    return order
}
