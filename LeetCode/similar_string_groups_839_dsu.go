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

func numSimilarGroups(strs []string) int {
    ids := make(map[string]int)

    for _, word := range strs {
        if _, already := ids[word]; !already {
            id := len(ids)
            ids[word] = id
        }
    }

    unique := len(ids)

    dsu := makeDSU(unique)

    ans := unique

    seen := make([]bool, unique)

    for i, word := range strs {
        id := ids[word]
        if seen[id] {
            continue
        }

        seen[id] = true
        size := len(word)

        for j := 0; j < i; j++ {
            j_word := strs[j]

            diffs := 0
            for k := 0; k < size; k++ {
                if word[k] != j_word[k] {
                    diffs++
                }
            }

            if diffs != 2 {
                continue
            }

            j_id := ids[j_word]

            if dsu.Merge(id, j_id) {
                ans--
            }
        }
    }

    return ans
}
