func longestObstacleCourseAtEachPosition(obstacles []int) []int {
    n := len(obstacles)

    inf := -1
    for _, value := range obstacles {
        if inf < value {
            inf = value
        }
    }
    inf++

    lenToMin := make([]int, n + 1)
    for i := range lenToMin {
        lenToMin[i] = inf
    }
    lenToMin[0] = -1

    answer := make([]int, n)
    for i, value := range obstacles {
        left, right := -1, n + 1
        for ; left + 1 < right; {
            mid := (left + right) / 2
            if lenToMin[mid] > value {
                right = mid
            } else {
                left = mid
            }
        }

        answer[i] = right
        lenToMin[right] = value
    }

    return answer
}
