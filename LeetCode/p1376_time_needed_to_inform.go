func numOfMinutes(n int, headId int, managers []int, informTimes []int) int {
    graph := make([][]int, n)
    for v, manager := range managers {
        if v == headId {
            continue
        }

        graph[manager] = append(graph[manager], v)
    }

    var calculateTime func(int) int
    calculateTime = func(v int) int {
        maxChildTime := 0
        for _, child := range graph[v] {
            childTime := calculateTime(child)
            if maxChildTime < childTime {
                maxChildTime = childTime
            }
        }
        
        return maxChildTime + informTimes[v]
    }

    return calculateTime(headId)
}
