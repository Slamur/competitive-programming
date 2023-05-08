func distinctDifferenceArray(nums []int) []int {
    n := len(nums)
    answer := make([]int, n)

    set := make(map[int]bool)
    for i, value := range nums {
        set[value] = true
        answer[i] += len(set)
    }

    set = make(map[int]bool)
    for i := n - 1; i >= 0; i-- {
        answer[i] -= len(set)
        value := nums[i]
        set[value] = true
    }

    return answer
}
