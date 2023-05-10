// provides interface for iterator over matrix cells
type MatrixIterator interface {
    Has() bool
    Get() (int, int, bool)
}

type Step [2]int

var LEFT = Step{0, 1}
var RIGHT = Step{0, -1}
var DOWN = Step{1, 0}
var UP = Step{-1, 0}
