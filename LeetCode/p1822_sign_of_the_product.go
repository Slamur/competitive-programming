func signum(num int) int {
    if num < 0 {
        return -1
    }
    if num > 0 {
        return 1
    }
    return 0
}

func arraySign(nums []int) int {
    answer := 1

    for _, num := range nums {
        answer *= signum(num)
    }

    return answer
}
