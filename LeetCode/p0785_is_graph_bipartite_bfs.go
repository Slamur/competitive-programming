func isBipartite(graph [][]int) bool {
    n := len(graph)
    colors := make([]int, n)
    
    for start := range graph {
        if 0 != colors[start] {
            continue
        }

        q := make([]int, 0)

        q = append(q, start)
        colors[start] = 1

        for it := 0; it < len(q); it++ {
            v := q[it]
            vColor := colors[v]

            for _, to := range graph[v] {
                toColor := colors[to]
                if 0 == toColor {
                    q = append(q, to)
                    colors[to] = -vColor
                } else {
                    if colors[to] != -vColor {
                        return false   
                    }
                }
            }
        }
    }

    return true
}
