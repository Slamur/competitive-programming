func findCircleNum(isConnected [][]int) int {
    var dfs func(int) bool

    n := len(isConnected)
    used := make([]bool, n)
    dfs = func(v int) bool {
        if used[v] {
            return false
        }

        used[v] = true

        for to, edge := range isConnected[v] {
            if edge == 1 {
                dfs(to)
            }
        }

        return true
    }

    components := 0
    for v := range used {
        if dfs(v) {
            components++
        }
    }

    return components
}
