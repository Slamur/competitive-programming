func maxStrength(nums []int) int64 {
    ans := int64(nums[0])
    
    n := len(nums)
    for mask, lim := 1, (1 << n); mask < lim; mask++ {
        strength := int64(1)
        for i, num := range nums {
            if ((mask >> i) & 1) == 0 {
                continue
            }
            
            strength *= int64(num)
        }
        
        if ans < strength {
            ans = strength
        }
    }
    
    return ans
}
