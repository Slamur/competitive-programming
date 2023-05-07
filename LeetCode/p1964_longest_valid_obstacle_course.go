func longestObstacleCourseAtEachPosition(obstacles []int) []int {
    n := len(obstacles)

    lenToMin := make([]int, 1, n + 1)
    lenToMin[0] = -1

    answer := make([]int, n)
    for i, value := range obstacles {
        firstLarger := sort.Search(len(lenToMin), func(mid int) bool {
            return lenToMin[mid] > value
        })

        if len(lenToMin) == firstLarger {
            lenToMin = append(lenToMin, -1)
        }

        answer[i] = firstLarger
        lenToMin[firstLarger] = value
    }

    return answer
}
