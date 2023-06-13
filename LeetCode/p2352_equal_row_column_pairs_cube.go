func equalPairs(grid [][]int) int {
    ans := 0

    for _, row := range grid {
        for c := range row {
            equal := true
            for i := range grid {
                equal = equal && (row[i] == grid[i][c])
            }
            if equal {
                ans++
            }
        }
    }

    return ans
}
