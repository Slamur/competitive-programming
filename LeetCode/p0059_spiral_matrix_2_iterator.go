type MatrixIterator interface {
    Has() bool
    Get() (int, int, bool)
}

type SpiralIterator struct {
    xSize, ySize int

    used []bool
    usedCount int

    steps [][2]int
    direction int
    x, y int
    cell int
}

func spiral(xSize, ySize int, steps [][2]int) *SpiralIterator {
    total := xSize * ySize

    direction := 0
    return &SpiralIterator {
        xSize: xSize,
        ySize: ySize,

        used: make([]bool, total),
        usedCount: 0,

        steps: steps,
        direction: direction,
        x: 0,
        y: 0,
        cell: 0,
    }
}

func (it *SpiralIterator) canStep(nextX, nextY int) (canStep bool, cell int) {
    if nextX < 0 || it.xSize <= nextX {
        return false, -1
    }

    if nextY < 0 || it.ySize <= nextY {
        return false, -1
    }

    cell = nextX * it.ySize + nextY
    return !it.used[cell], cell
}

func (it *SpiralIterator) Has() bool {
    if it.usedCount == len(it.used) {
        return false
    }

    for ; it.used[it.cell]; {
        step := &it.steps[it.direction]
        nextX, nextY := it.x + step[0], it.y + step[1]

        canStep, nextCell := it.canStep(nextX, nextY)
        if !canStep {
            it.direction = (it.direction + 1) % 4
        } else {
            it.x, it.y, it.cell = nextX, nextY, nextCell
        }
    }

    return true
}

func (it *SpiralIterator) Get() (x int, y int, has bool){
    if !it.Has() {
        return -1, -1, false
    }

    it.used[it.cell] = true
    it.usedCount++

    return it.x, it.y, true
}

func generateMatrix(n int) [][]int {
    xSize, ySize := n, n

    steps := [][2]int {
        { 0, 1 },
        { 1, 0 },
        { 0, -1 },
        { -1, 0 },
    }

    answer := make([][]int, xSize)
    for x := range answer {
        answer[x] = make([]int, ySize)
    }

    for value, it := 1, spiral(xSize, ySize, steps); it.Has(); value++ {
        x, y, _ := it.Get()
        answer[x][y] = value
    }

    return answer   
}
