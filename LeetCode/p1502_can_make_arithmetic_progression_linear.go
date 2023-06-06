// O(N) solution
func canMakeArithmeticProgression(arr []int) bool {
    values := make(map[int]bool)
    for _, value := range arr {
        values[value] = true
    }

    min, max := arr[0], arr[0]
    for _, value := range arr {
        if min > value {
            min = value
        }

        if max < value {
            max = value
        }
    }

    delta := max - min
    n := len(arr)
    if delta % (n - 1) != 0 {
        return false
    }

    delta /= (n - 1)

    for i := 0; i < n; i++ {
        expected := min + i * delta
        if !values[expected] {
            return false
        }
    }

    return true
}
