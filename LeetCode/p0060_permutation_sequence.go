import (
    "strings"
)

func getPermutation(n int, k int) string {
    facts := make([]int, n + 1)
    facts[0] = 1
    for i := 1; i <= n; i++ {
        facts[i] = facts[i - 1] * i
    }

    k--

    var sb strings.Builder

    used := make([]bool, n + 1)
    for i := n - 1; i >= 0; i-- {
        for cur := 1; cur <= n; cur++ {
            if used[cur] {
                continue
            }

            if k >= facts[i] {
                k -= facts[i]
            } else {
                used[cur] = true
                sb.WriteRune(rune(cur + int('0')))
                break
            }
        }
    }

    return sb.String()
}
