// Example from https://pkg.go.dev/container/heap

// An IntHeap is a min-heap of ints.
type IntHeap []int

func (h IntHeap) Len() int           { return len(h) }
func (h IntHeap) Less(i, j int) bool { return h[i] < h[j] }
func (h IntHeap) Swap(i, j int)      { h[i], h[j] = h[j], h[i] }
func (h IntHeap) Peek() int          { return h[0] }

func (h *IntHeap) Push(value any) {
	// Push and Pop use pointer receivers because they modify the slice's length,
	// not just its contents.
	*h = append(*h, value.(int))
}

func (h *IntHeap) Pop() any {
	old := *h
	n := len(old)
	value := old[n-1]
	*h = old[0 : n-1]
	return value
}

type KthLargest struct {
    h *IntHeap
    k int
}

func Constructor(k int, nums []int) KthLargest {
    largest := KthLargest {
        h: &IntHeap{},
        k: k,
    }

    for _, value := range nums {
        largest.Add(value)
    }

    return largest
}

func (this *KthLargest) Add(val int) int {
    heap.Push(this.h, val)
    if this.h.Len() > this.k {
        heap.Pop(this.h)
    }
    return this.h.Peek()
}


/**
 * Your KthLargest object will be instantiated and called as such:
 * obj := Constructor(k, nums);
 * param_1 := obj.Add(val);
 */
