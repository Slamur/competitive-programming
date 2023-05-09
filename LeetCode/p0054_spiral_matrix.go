func spiralOrder(matrix [][]int) []int {
    xSize, ySize := len(matrix), len(matrix[0])

    total := xSize * ySize
    answer := make([]int, 0, total)

    steps := [...][2]int {
        { 0, 1 },
        { 1, 0 },
        { 0, -1 },
        { -1, 0 },
    }

    used := make([]bool, total)

    canStep := func(nextX, nextY int) (canStep bool, cell int) {
        if nextX < 0 || xSize <= nextX {
            return false, -1
        }

        if nextY < 0 || ySize <= nextY {
            return false, -1
        }

        cell = nextX * ySize + nextY
        return !used[cell], cell
    }

    direction := 0
    for x, y := -steps[direction][0], -steps[direction][1]; len(answer) < total; {
        step := &steps[direction]
        nextX, nextY := x + step[0], y + step[1]

        canStep, cell := canStep(nextX, nextY)
        if !canStep {
            direction = (direction + 1) % 4
        } else {
            answer = append(answer, matrix[nextX][nextY])
            used[cell] = true
            x, y = nextX, nextY
        }
    }

    return answer
}
