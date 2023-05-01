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

type Event struct {
    Value int
    Type int
    Index int
}

func distanceLimitedPathsExist(n int, edgeList [][]int, queries [][]int) []bool {
    e_size := len(edgeList)
    q_size := len(queries)

    events := make([]Event, e_size + q_size)

    query_type := 0
    edge_type := 1 // query before edge

    for i, edge := range edgeList {
        events[i] = Event {
            Value: edge[2],
            Type: edge_type,
            Index: i,
        }
    }

    for j, query := range queries {
        events[j + e_size] = Event {
            Value: query[2],
            Type: query_type,
            Index: j,
        }
    }

    sort.Slice(events, func (i, j int) bool {
        i_event, j_event := events[i], events[j]

        value_cmp := i_event.Value - j_event.Value
        if value_cmp != 0 {
            return value_cmp < 0
        }

        return i_event.Type < j_event.Type
    })

    dsu := makeDSU(n)

    answers := make([]bool, q_size)

    for _, event := range events {
        if event.Type == query_type {
            query := queries[event.Index]
            from, to := query[0], query[1]
            answers[event.Index] = dsu.Get(from) == dsu.Get(to)
        } else {
            edge := edgeList[event.Index]
            from, to := edge[0], edge[1]
            dsu.Merge(from, to)
        }
    }

    return answers
}
