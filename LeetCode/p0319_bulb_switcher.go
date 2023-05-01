import(
    "math"
)

func bulbSwitch(n int) int {
    n64 := float64(n)
    return int(math.Sqrt(n64))
}
