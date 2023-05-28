func minExtraChar(s string, dictionary []string) int {
    n := len(s)
    
    words := make(map[string]bool)
    for _, word := range dictionary {
        words[word] = true
    }
    
    dp := make([]int, n + 1)
    for start := n - 1; start >= 0; start-- {
        dp[start] = dp[start + 1] + 1
        
        for end := start; end <= n; end++ {
            word := s[start : end]
            if words[word] {
                if dp[start] > dp[end] {
                    dp[start] = dp[end]
                }
            }
        }
    }
    
    return dp[0]
}
