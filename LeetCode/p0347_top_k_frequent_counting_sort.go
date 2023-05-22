func topKFrequent(nums []int, k int) []int {
    counts := make(map[int]int)
    for _, value := range nums {
        counts[value]++
    }

    countToValues := make(map[int][]int)
    for value, count := range counts {
        countToValues[count] = append(countToValues[count], value)
    }

    answer := make([]int, 0, k)
    for count := len(nums); count > 0; count-- {
        countValues := countToValues[count]
        for i := 0; i < len(countValues) && len(answer) < k; i++ {
            answer = append(answer, countValues[i])
        }
    }

    return answer
}
