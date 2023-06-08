func countNegatives(grid [][]int) int {
    rowSize, colSize := len(grid), len(grid[0])

    ans := 0
    for row, lastNegativeCol := 0, colSize; row < rowSize; row++ {
        for ; lastNegativeCol > 0 && grid[row][lastNegativeCol - 1] < 0; lastNegativeCol-- {}
        ans += colSize - lastNegativeCol
    }

    return ans
}
