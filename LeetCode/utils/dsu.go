// DSU is 'disjoint set union', also known as 'union-find'
// Details: 
//  - [e-maxx]: https://e-maxx.ru/algo/dsu
//  - [cp-algorithms]: https://cp-algorithms.com/data_structures/disjoint_set_union.html
//  - [CF Edu]: https://codeforces.com/edu/course/2/lesson/7
type DSU struct {
    parents []int
    sizes []int
}

// Returns 'root' of component with vertex 'v'
// Performs 'path compression' euristic during search
func (dsu *DSU) Get(v int) int {
    p := dsu.parents[v]
    if p == v {
        return p
    }

    dsu.parents[v] = dsu.Get(p)
    return dsu.parents[v]
}

// Tries to merge components with vertices 'a' and 'b'
// Returns 'true' if actual merge was done
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

// Creates DSU instance with 'n' non-connected vertices
func makeDSU(size int) *DSU {
    parents := make([]int, size)
    sizes := make([]int, size)
    for v := 0; v < size; v++ {
        parents[v] = v
        sizes[v] = 1
    }

    return &DSU {
        parents: parents,
        sizes: sizes,
    }
}
