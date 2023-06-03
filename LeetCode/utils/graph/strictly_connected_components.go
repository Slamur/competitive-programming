func inverse(graph [][]int) (inverseGraph [][]int) {
    n := len(graph)

    inverseGraph = make([][]int, n)
    for v, edges := range graph {
        for _, to := range edges {
            inverseGraph[to] = append(inverseGraph[to], v)
        }
    }

    return inverseGraph
}

func calculateSccColors(graph [][]int) (componentsCount int, colors []int) {
    order := topologicalSort(graph)
    inverseGraph := inverse(graph)

    n := len(order)

    colors = make([]int, n)
    for v := range graph {
        colors[v] = -1
    }

    var sccDfs func(int, int)
    sccDfs = func(v, color int) {
        if colors[v] != -1 {
            return
        }

        colors[v] = color

        for _, to := range inverseGraph[v] {
            sccDfs(to, color)
        }
    }

    componentsCount = 0
    for i := n - 1; i >= 0; i-- {
        v := order[i]
        if colors[v] == -1 {
            sccDfs(v, componentsCount)
            componentsCount++
        }
    }

    return componentsCount, colors
}

func strictlyConnectedComponents(graph [][]int) (components [][]int, componentsGraph [][]int) {
    componentsCount, colors := calculateSccColors(graph)

    components = make([][]int, componentsCount)
    for v, color := range colors {
        components[color] = append(components[color], v)
    }

    componentsGraph = make([][]int, componentsCount)

    usedEdges := make(map[[2]int]bool)

    for v, edges := range graph {
        vColor := colors[v]

        for _, to := range edges {
            toColor := colors[to]
            if vColor != toColor {
                cacheKey := [2]int{vColor, toColor}
                if !usedEdges[cacheKey] {
                    componentsGraph[vColor] = append(componentsGraph[vColor], toColor)
                    usedEdges[cacheKey] = true
                }
            }
        }
    }

    return components, componentsGraph
}
