func maximumDetonation(bombs [][]int) int {
    var detonates func(int, int) bool
    detonates = func(from, to int) bool {
        dx := int64(bombs[to][0] - bombs[from][0])
        dy := int64(bombs[to][1] - bombs[from][1])
        r := int64(bombs[from][2])

        return dx * dx + dy * dy <= r * r
    }

    n := len(bombs)

    graph := make([][]int, n)
    for i := range graph {        
        for j := range bombs {
            if detonates(i, j) {
                graph[i] = append(graph[i], j)
            }
        }
    }

    best := 0

    for start := range graph {
        q := []int { start }

        used := make([]bool, n)
        used[start] = true

        for i := 0; i < len(q); i++ {
            v := q[i]
            for _, to := range graph[v] {
                if used[to] {
                    continue
                }

                used[to] = true
                q = append(q, to)
            }
        }

        if best < len(q) {
            best = len(q)
        }
    }

    return best
}
