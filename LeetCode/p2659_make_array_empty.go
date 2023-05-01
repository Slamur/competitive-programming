func countOperationsToEmptyArray(nums []int) int64 {
    n := len(nums)
    
    pos := make(map[int]int)
    for i, value := range nums {
        pos[value] = i
    }

    sort.Ints(nums)

    ans := int64(n)
    for i := n - 2; i >= 0; i-- {
        if pos[nums[i]] > pos[nums[i + 1]] {
            ans += int64(n - 1 - i)
        }
    }
    
    return ans
}
