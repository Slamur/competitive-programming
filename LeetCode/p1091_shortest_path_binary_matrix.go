func shortestPathBinaryMatrix(grid [][]int) int {
    q := [][3]int {
        [3]int{ -1, -1, 0, },
    }

    n := len(grid)

    endX, endY := n - 1, n - 1

    for i := 0; i < len(q); i++ {
        v := q[i]
        x, y, d := v[0], v[1], v[2]

        if x == endX && y == endY {
            return d
        }

        for dx := -1; dx <= 1; dx++ {
            for dy := -1; dy <= 1; dy++ {
                tx, ty := x + dx, y + dy
                if tx < 0 || n <= tx {
                    continue
                }

                if ty < 0 || n <= ty {
                    continue
                }

                if grid[tx][ty] == 1 {
                    continue
                }

                grid[tx][ty] = 1
                q = append(q, [3]int{ tx, ty, d + 1, } )
            }
        }
    }

    return -1
}
