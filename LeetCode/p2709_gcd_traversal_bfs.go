func canTraverseAllPairs(nums []int) bool {
    hasOnes := false
    for _, val := range nums {
        if val == 1 {
            hasOnes = true
        }
    }
    
    if hasOnes {
        return len(nums) == 1
    }
    
    maxA := 100 * 1000
    
    used := make([]bool, maxA + 10)
    for _, num := range nums {
        used[num] = true
    }
    
    size := maxA + maxA + 10
    
    graph := make([][]int, size)
    for d := 2; d <= maxA; d++ {
        v := maxA + 1 + d
        for i := d; i <= maxA; i += d {
            if used[i] {
                graph[v] = append(graph[v], i)
                graph[i] = append(graph[i], v)
            }
        }
    }
    
    vis := make([]bool, size)
    
    start := nums[0]
    q := []int { start }
    vis[start] = true
    
    for i := 0; i < len(q); i++ {
        v := q[i]
        for _, to := range graph[v] {
            if vis[to] {
                continue
            }
            
            vis[to] = true
            q = append(q, to)
        }
    }
    
    for _, num := range nums {
        if !vis[num] {
            return false
        }
    }
    
    return true
}
