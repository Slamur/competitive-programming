// iterates over all matrix cells in spiral order based on steps
// matches the [MatrixIterator] interface
//
// Example of SpiralIterator using:
//
//  func spiralOrder(rowsCount, columnsCount int) [][2]int {
//    steps := []Step {
//        LEFT,
//        DOWN,
//        RIGHT,
//        UP,
//    }
//    
//    answer := make([][2]int, 0, rowsCount * columnsCount)
//    for it := spiral(rowsCount, columnsCount, steps); it.Has(); {
//        row, column, _ := it.Get()
//        answer = append(answer, [2]int{row, column})
//    }
//
//    return answer
//  }
//
type SpiralIterator struct {
    rowsCount, columnsCount int

    used []bool
    usedCount int

    steps []Step
    direction int
    row, column int
    cell int
}

// creates SpiralIterator from top-left corner
func spiral(rowsCount, columnsCount int, steps []Step) *SpiralIterator {
    total := rowsCount * columnsCount

    direction := 0
    return &SpiralIterator {
        rowsCount: rowsCount,
        columnsCount: columnsCount,

        used: make([]bool, total),
        usedCount: 0,

        steps: steps,
        direction: direction,
        row: 0,
        column: 0,
        cell: 0,
    }
}

// checks if (nextX, nextY) is valid cell to go
func (it *SpiralIterator) canStep(nextRow, nextColumn int) (canStep bool, cell int) {
    if nextRow < 0 || it.rowsCount <= nextRow {
        return false, -1
    }

    if nextColumn < 0 || it.columnsCount <= nextColumn {
        return false, -1
    }

    cell = nextRow * it.columnsCount + nextColumn
    return !it.used[cell], cell
}

// checks if there is any unused cell
// moves to the next unused cell in spiral order
func (it *SpiralIterator) Has() bool {
    if it.usedCount == len(it.used) {
        return false
    }

    for ; it.used[it.cell]; {
        step := &it.steps[it.direction]
        nextRow, nextColumn := it.row + step[0], it.column + step[1]

        canStep, nextCell := it.canStep(nextRow, nextColumn)
        if !canStep {
            it.direction = (it.direction + 1) % len(it.steps)
        } else {
            it.row, it.column, it.cell = nextRow, nextColumn, nextCell
        }
    }

    return true
}

// returns coordinates of the next unused cell in spiral order
// third parameter is Has() call result
func (it *SpiralIterator) Get() (row int, column int, has bool){
    if !it.Has() {
        return -1, -1, false
    }

    it.used[it.cell] = true
    it.usedCount++

    return it.row, it.column, true
}
