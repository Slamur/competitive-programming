func firstMissingPositive(nums []int) int {
    n := len(nums)
    for i := range nums {
        for num := nums[i]; 1 <= num && num <= n; num = nums[i] {
            if num == i + 1 {
                break
            }

            newNum := nums[num - 1]
            if newNum == num {
                nums[i] = -1
                break
            }

            nums[i] = newNum
            nums[num - 1] = num
        }
    }

    for i, num := range nums {
        if num != i + 1 {
            return i + 1
        }
    }

    return n + 1
}
