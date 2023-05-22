func partition(values []int, left, right int) int {
    mid := left + rand.Intn(right - left + 1)
    midValue := values[mid]

    values[mid], values[right] = values[right], values[mid]

    firstLarger := left
    for i := left; i < right; i++ {
        if values[i] < midValue {
            values[i], values[firstLarger] = values[firstLarger], values[i]
            firstLarger++
        }
    }

    values[firstLarger], values[right] = values[right], values[firstLarger]

    return firstLarger
}

func findKthStatistic(values []int, k int) {
    k--

    for left, right := 0, len(values) - 1; left <= right; {
        mid := partition(values, left, right)

        if mid == k {
            break
        }

        if mid > k {
            right = mid - 1
        } else {
            left = mid + 1
        }
    }
}
