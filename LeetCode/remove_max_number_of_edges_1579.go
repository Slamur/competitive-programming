type DSU struct {
    parents []int
    sizes []int
}

func (dsu *DSU) Get(v int) int {
    p := dsu.parents[v]
    if p == v {
        return p
    }

    dsu.parents[v] = dsu.Get(p)
    return dsu.parents[v]
}

func (dsu *DSU) Merge(a int, b int) bool {
    ra := dsu.Get(a)
    rb := dsu.Get(b)

    if ra == rb {
        return false
    }

    sa := dsu.sizes[ra]
    sb := dsu.sizes[rb]

    if sa < sb {
        ra, rb = rb, ra
        sa, sb = sb, sa
    }

    dsu.parents[rb] = ra
    dsu.sizes[ra] += sb

    return true
}

func makeDSU(size int) DSU {
    parents := make([]int, size)
    sizes := make([]int, size)
    for v := 0; v < size; v++ {
        parents[v] = v
        sizes[v] = 1
    }

    return DSU {
        parents: parents,
        sizes: sizes,
    }
}

func calculateComponents(n int, edges [][]int, expectedEdgeTypes []int) int {
    dsu := makeDSU(n)

    components := n
    for _, edge := range edges {
        actualEdgeType := edge[0]

        isExpected := false
        for _, expectedEdgeType := range expectedEdgeTypes {
            isExpected = isExpected || expectedEdgeType == actualEdgeType
        }

        if isExpected {
            if dsu.Merge(edge[1] - 1, edge[2] - 1) {
                components--
            }
        }
    }

    return components
}

func maxNumEdgesToRemove(n int, edges [][]int) int {
    aliceType, bobType, bothType := 1, 2, 3

    aliceComponents := calculateComponents(n, edges, []int{aliceType, bothType})
    bobComponents := calculateComponents(n, edges, []int{bobType, bothType})
    bothComponents := calculateComponents(n, edges, []int{bothType})

    if aliceComponents > 1 || bobComponents > 1 {
        return -1
    }

    needEdges := n - 1 + bothComponents - 1
    totalEdges := len(edges)

    return totalEdges - needEdges
}
