func findSmallestSetOfVertices(n int, edges [][]int) []int {
    inDegrees := make([]int, n)
    for _, edge := range edges {
        inDegrees[edge[1]]++
    }

    ans := make([]int, 0)
    for v, inDegree := range inDegrees {
        if inDegree == 0 {
            ans = append(ans, v)
        }
    }

    return ans
}
