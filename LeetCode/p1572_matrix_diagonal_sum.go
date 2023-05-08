func diagonalSum(mat [][]int) int {
    answer := 0

    n := len(mat)
    for i, row := range mat {
        answer += row[i] + row[n - i - 1]
    }

    if n % 2 == 1 {
        answer -= mat[n / 2][n / 2]
    }

    return answer
}
