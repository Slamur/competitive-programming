func maxValue(n int, index int, maxSum int) int {
    var sum func(int, int) int64
    sum = func(right, left int) int64 {
        size := right - left + 1
        return int64(size) * int64(right + left) / 2
    }

    var max func(int, int) int
    max = func(a, b int) int {
        if a > b {
            return a
        }
        return b
    }

    leftDistance, rightDistance := index, n - index - 1

    left, right := 0, maxSum + 1
    for left + 1 < right {
        mid := (left + right) / 2

        leftSum := sum(mid, max(0, mid - leftDistance))
        rightSum := sum(mid, max(0, mid - rightDistance))

        totalSum := leftSum + rightSum - int64(mid) + int64(n)
        if totalSum <= int64(maxSum) {
            left = mid
        } else {
            right = mid
        }
    }

    return left + 1
}
