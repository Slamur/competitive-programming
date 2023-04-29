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
    sizes := make([]int, 1)
    
    for _, value := range nums {
        prev := value - 1
        
        var color int
        if prev < 0 || colors[prev] == 0 {
            color = len(sizes)
            sizes = append(sizes, 0)
        } else {
            color = colors[prev]
        }
        
        colors[value] = color
        sizes[color]++
    }
    
    ans := int64(n)
    
    suffix := 0
    for i := n - 2; i >= 0; i-- {
        if colors[i] != colors[i + 1] {
            suffix += sizes[colors[i + 1]]
            ans += int64(suffix)
        }
    }
    
    return ans
}
