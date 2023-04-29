func countOperationsToEmptyArray(nums []int) int64 {
    n := len(nums)
    
    sorted := make([]int, n)
    copy(sorted, nums)
    sort.Ints(sorted)
    
    for i := 0; i < n; i++ {
        value := nums[i]
        nums[i] = sort.SearchInts(sorted, value)
    }
    
    colors := make([]int, n) // 0 - not used
    next_color := 1
    
    for _, value := range nums {
        prev := value - 1
        
        var color int
        if prev < 0 || colors[prev] == 0 {
            color = next_color
        } else {
            color = colors[prev]
        }
        
        colors[value] = color
    }
    
    ans := int64(n)
    
    for i := n - 2; i >= 0; i-- {
        if colors[i] != colors[i + 1] {
            ans += int64(n - 1 - i)
        }
    }
    
    return ans
}
