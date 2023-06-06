func canMakeArithmeticProgression(arr []int) bool {
    sort.Ints(arr)

    delta := arr[1] - arr[0]
    for i, value := range arr {
        if value - arr[0] != i * delta {
            return false
        }
    }

    return true
}
