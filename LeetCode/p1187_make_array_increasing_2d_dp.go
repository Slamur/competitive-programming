type Compressor struct {
    values map[int]bool
    unique []int
}

func start() *Compressor {
    return &Compressor {
        values: make(map[int]bool),
        unique: make([]int, 0),
    }
}

func (compressor *Compressor) register(arr []int) {
    for _, val := range arr {
        compressor.values[val] = true
    }
}

func (compressor *Compressor) build() {
    size := len(compressor.values)
    unique := make([]int, 0, size)
    for val, _ := range compressor.values {
        unique = append(unique, val)
    }

    sort.Ints(unique)
    compressor.unique = unique
}

func (compressor *Compressor) id(x int) int {
    return sort.SearchInts(compressor.unique, x)
}

func makeArrayIncreasing(target []int, source []int) int {
    compressor := start()

    compressor.register(target)
    compressor.register(source)

    compressor.build()

    size := len(compressor.unique)

    n := len(target)
    no_ans := n + 1

    dp := make([][]int, n + 1)
    for i := range dp {
        dp[i] = make([]int, size + 1)
        for j := range dp[i] {
            dp[i][j] = no_ans
        }
    }

    available := make(map[int]bool)
    for _, val := range source {
        available[compressor.id(val)] = true
    }

    dp[0][0] = 0
    for id := 1; id <= size; id++ {
        dp[0][id] = dp[0][id - 1]
    }

    for i, i_val := range target {
        i_id := compressor.id(i_val)

        for last_id := 0; last_id < size; last_id++ {
            cost := no_ans
            if last_id == i_id {
                cost = 0
            } else if available[last_id] {
                cost = 1
            }

            if dp[i + 1][last_id + 1] > dp[i + 1][last_id] {
                dp[i + 1][last_id + 1] = dp[i + 1][last_id]
            }

            if dp[i + 1][last_id + 1] > dp[i][last_id] + cost {
                dp[i + 1][last_id + 1] = dp[i][last_id] + cost
            }
        }
    }

    ans := dp[n][size]

    if no_ans == ans {
        return -1
    }

    return ans
}
