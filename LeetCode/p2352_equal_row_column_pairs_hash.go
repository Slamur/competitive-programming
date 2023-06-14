func isPrime(x int) bool {
    for d := 2; d * d <= x; d++ {
        if x % d == 0 {
            return false
        }
    }

    return true
}

func genPrime(start int) int64 {
    for ; !isPrime(start); start++ { }
    return int64(start)
}

type Hasher struct {
    mod     int64
    mult    int64
}

func initHasher(maxValue int) *Hasher {
    return &Hasher {
        mod: genPrime(1000 * 1000 * 1000 + 123),
        mult: genPrime(maxValue + 456),
    }
}

func (hasher *Hasher) calculate(array []int) int {
    var hash int64 = 0
    for _, value := range array {
        hash *= hasher.mult
        hash += int64(value)
        hash %= hasher.mod
    }

    return int(hash)
}

func equalPairs(grid [][]int) int {
    maxValue := 100 * 1000
    hasher := initHasher(maxValue)

    rowCounts := make(map[int]int)
    for _, row := range grid {
        rowCounts[hasher.calculate(row)]++
    }

    extractColumn := func(columnIndex int) []int {
        column := make([]int, len(grid))
        for i := range grid {
            column[i] = grid[i][columnIndex]
        }
        return column
    }

    ans := 0

    for columnIndex := range grid[0] {
        column := extractColumn(columnIndex)
        ans += rowCounts[hasher.calculate(column)]
    }

    return ans
}
