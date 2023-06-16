func numOfWays(nums []int) int {
    var mod int64 = 1000 * 1000 * 1000 + 7

    n := len(nums)
    binom := make([][]int64, n + 1)
    for i := 0; i <= n; i++ {
        binom[i] = make([]int64, i + 1)
        binom[i][0] = 1
        binom[i][i] = 1
        for j := 1; j < i; j++ {
            binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % mod
        }
    }

    used := make([]bool, n + 1)

    var ans int64 = 1
    for _, root := range nums {
        left := root
        for ; left >= 1 && !used[left]; left-- { }

        right := root
        for ; right <= n && !used[right]; right++ { }

        ans *= binom[right - left - 2][root - left - 1]
        ans %= mod
        
        used[root] = true
    }

    ans += mod - 1
    ans %= mod

    return int(ans)
}
