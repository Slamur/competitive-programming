func getId(ids map[string]int, name string, register bool) int {
    id, has := ids[name]
    if !has {
        if !register {
            return -1
        }

        id = len(ids)
        ids[name] = id
    }

    return id
}

type Edge struct {
    to int
    weight float64
}

func calcEquation(equations [][]string, values []float64, queries [][]string) []float64 {
    ids := make(map[string]int)

    m := len(equations)
    edges := make([][2]int, m)

    for e, equation := range equations {
        from := getId(ids, equation[0], true)
        to := getId(ids, equation[1], true)

        edges[e] = [2]int { from, to }
    }

    n := len(ids)
    graph := make([][]Edge, n)

    for e, edge := range edges {
        from, to := edge[0], edge[1]
        weight := values[e]

        graph[from] = append(graph[from], Edge {
            to: to,
            weight: weight,
        })

        graph[to] = append(graph[to], Edge {
            to: from,
            weight: 1.0 / weight,
        })
    }

    distances := make([][]float64, n)
    for start := range distances {
        startDistances := make([]float64, n)
        for end := range startDistances {
            startDistances[end] = -1.0
        }

        startDistances[start] = 1.0
        q := []int { start }

        for it := 0; it < len(q); it++ {
            v := q[it]
            vDistance := startDistances[v]
            for _, edge := range graph[v] {
                if startDistances[edge.to] != -1.0 {
                    continue
                }

                startDistances[edge.to] = vDistance * edge.weight
                q = append(q, edge.to)
            }
        }

        distances[start] = startDistances
    }

    q := len(queries)
    answers := make([]float64, q)

    for qi, query := range queries {
        from := getId(ids, query[0], false)
        to := getId(ids, query[1], false)

        if from == -1 || to == -1 {
            answers[qi] = -1.0
        } else {
            answers[qi] = distances[from][to]
        }
    }

    return answers
}
