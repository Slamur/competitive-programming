package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

var (
	in  = bufio.NewReader(os.Stdin)
	out = bufio.NewWriter(os.Stdout)
)

func main() {
	defer out.Flush()
	solve()
}

func ri() int {
	var value int
	fmt.Fscan(in, &value)
	return value
}

func rll() int64 {
	var value int64
	fmt.Fscan(in, &value)
	return value
}

func rs() string {
	var value string
	fmt.Fscan(in, &value)
	return value
}

func rvi(size int) []int {
	array := make([]int, size)
	for i := 0; i < size; i++ {
		array[i] = ri()
	}
	return array
}

func rvll(size int) []int64 {
	array := make([]int64, size)
	for i := 0; i < size; i++ {
		array[i] = rll()
	}
	return array
}

func yes_no(result bool, yes, no string) bool {
	var ans string
	if result {
		ans = yes
	} else {
		ans = no
	}

	fmt.Fprintln(out, ans)
	return result
}

func min(a, b int) int {
	if a < b {
		return a
	} else {
		return b
	}
}

func max(a, b int) int {
	if a > b {
		return a
	} else {
		return b
	}
}

func abs(x int) int {
	if x < 0 {
		return -x
	}

	return x
}

func lower_bound(array []int, value int) int {
	left := -1
	right := len(array)
	for ; right - left > 1; {
		mid := (left + right) / 2
		if array[mid] >= value {
			right = mid
		} else {
			left = mid
		}
	}

	return right
}

func upper_bound(array []int, value int) int {
	return lower_bound(array, value + 1)
}

func clamp(value, left, right int) int {
	if value < left {
		return left
	}

	if value > right {
		return right
	}

	return value
}

func sort_vll(array []int64) {
	sort.Slice(array, func(i, j int) bool {
		return array[i] < array[j]
	})
}

func solve() {
	
}