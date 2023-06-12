func summaryRanges(nums []int) []string {
    segs := make([][2]int, 0)
    last := -1

    for _, value := range nums {
        if last < 0 || segs[last][1] + 1 < value {
            segs = append(segs, [2]int{ value, value })
            last++
        } else {
            segs[last][1] = value
        }
    }

    n := len(segs)
    segsStr := make([]string, n)

    for i, seg := range segs {
        start, end := seg[0], seg[1]

        if start < end {
            segsStr[i] = fmt.Sprintf("%d->%d", start, end)
        } else {
            segsStr[i] = fmt.Sprintf("%d", start)
        }
    }

    return segsStr
}
