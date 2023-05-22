type ValueCount struct {
    Value int
    Count int
}

func partition(values []ValueCount, left, right int) int {
    mid := left + rand.Intn(right - left + 1)
    midCount := values[mid].Count

    values[mid], values[right] = values[right], values[mid]

    firstLarger := left
    for i := left; i < right; i++ {
        if values[i].Count < midCount {
            values[i], values[firstLarger] = values[firstLarger], values[i]
            firstLarger++
        }
    }

    values[firstLarger], values[right] = values[right], values[firstLarger]

    return firstLarger
}

func findKthStatistic(values []ValueCount, k int) {
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

func topKFrequent(nums []int, k int) []int {
    counts := make(map[int]int)
    for _, value := range nums {
        counts[value]++
    }

    n := len(counts)

    values := make([]ValueCount, 0, n)
    for value, count := range counts {
        values = append(values, ValueCount {
            Value: value,
            Count: -count,
        })
    }

    findKthStatistic(values, k)

    answer := make([]int, k)
    for i := 0; i < k; i++ {
        answer[i] = values[i].Value
    }

    return answer
}
