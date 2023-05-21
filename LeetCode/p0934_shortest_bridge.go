type Step [2]int

var LEFT = Step{0, 1}
var RIGHT = Step{0, -1}
var DOWN = Step{1, 0}
var UP = Step{-1, 0}

var steps = [...]Step {
    LEFT,
    RIGHT,
    DOWN,
    UP,
}

func checkIndex(index, size int) bool {
    return 0 <= index && index < size
}

func checkCell(x, y, n int) bool {
    return checkIndex(x, n) && checkIndex(y, n)
}

func findStart(grid [][]int) int {
    for x, row := range grid {
        for y, cell := range row {
            if 1 == cell {
                return len(grid) * x + y
            }
        }
    }

    return -1
}

func findFirst(grid [][]int) []int {
    n := len(grid)

    start := findStart(grid)

    first := []int { start }
    used := make([]bool, n * n)
    used[start] = true

    for it := 0; it < len(first); it++ {
        v := first[it]
        x := v / n
        y := v - x * n

        for _, step := range steps {
            toX, toY := x + step[0], y + step[1]
            if !checkCell(toX, toY, n) {
                continue
            }

            if 0 == grid[x][y] {
                continue
            }

            to := toX * n + toY
            if used[to] {
                continue
            }

            first = append(first, to)
            used[to] = true
        }
    }

    return first
}

func shortestBridge(grid [][]int) int {
    n := len(grid)

    first := findFirst(grid)

    distances := make([]int, n * n)
    for v := range distances {
        distances[v] = -1
    }

    for _, v := range first {
        distances[v] = 0
    }

    for it := 0; it < len(first); it++ {
        v := first[it]
        x := v / n
        y := v - x * n

        distance := distances[v]

        if 1 == grid[x][y] && distance != 0 {
            return distance
        }

        for _, step := range steps {
            toX, toY := x + step[0], y + step[1]
            if !checkCell(toX, toY, n) {
                continue
            }

            to := toX * n + toY
            if distances[to] != -1 {
                continue
            }

            first = append(first, to)
            distances[to] = distance + 1
        }
    }

    return -1
}
