func largestAltitude(gain []int) int {
    ans := 0

    sum := 0
    for _, v := range gain {
        sum += v
        if ans < sum {
            ans = sum
        }
    }

    return ans
}
