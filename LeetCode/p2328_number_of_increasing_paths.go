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

func checkCell(x, y, r, c int) bool {
    return checkIndex(x, r) && checkIndex(y, c)
}

func countPaths(grid [][]int) int {
    r, c := len(grid), len(grid[0])

    order := make([][2]int, 0, r * c)
    for x, row := range grid {
        for y := range row {
            order = append(order, [2]int {x, y})
        }
    }

    sort.Slice(order, func(i, j int) bool {
        xi, yi := order[i][0], order[i][1]
        xj, yj := order[j][0], order[j][1]
        return grid[xi][yi] < grid[xj][yj]
    })

    dp := make([][]int, r)
    for x := range grid {
        dp[x] = make([]int, c)
        for y := range dp[x] {
            dp[x][y] = 1
        }
    }

    mod := 1000 * 1000 * 1000 + 7

    for _, cell := range order {
        x, y := cell[0], cell[1]
        for _, step := range steps {
            dx, dy := step[0], step[1]
            xx, yy := x + dx, y + dy

            if !checkCell(xx, yy, r, c) {
                continue
            }

            if grid[xx][yy] >= grid[x][y] {
                continue
            }

            dp[x][y] += dp[xx][yy]
            if dp[x][y] >= mod {
                dp[x][y] -= mod
            }
        }
    }

    ans := 0
    for _, row := range dp {
        for _, cell := range row {
            ans += cell
            if ans >= mod {
                ans -= mod
            }
        }
    }

    return ans
}
