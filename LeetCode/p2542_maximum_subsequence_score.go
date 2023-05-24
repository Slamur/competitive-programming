type Pair struct {
    SumValue int64
    MinValue int64
}

type ByMin []Pair

func (s ByMin) Len() int {
    return len(s)
}

func (s ByMin) Swap(i, j int) {
    s[i], s[j] = s[j], s[i]
}

func (s ByMin) Less(i, j int) bool {
    return s[i].MinValue > s[j].MinValue
}

type IntHeap []int64

func (s IntHeap) Len() int {
    return len(s)
}

func (s IntHeap) Swap(i, j int) {
    s[i], s[j] = s[j], s[i]
}

func (s IntHeap) Less(i, j int) bool {
    return s[i] < s[j]
}

func (s *IntHeap) Push(x any) {
    (*s) = append(*s, x.(int64))
}

func (s *IntHeap) Pop() any {
    old := *s
    n := len(old) - 1

    last := old[n]
    (*s) = old[:n]

    return last
}

func maxScore(nums1 []int, nums2 []int, k int) int64 {
    n := len(nums1)

    pairs := make([]Pair, 0, n)
    for i := 0; i < n; i++ {
        pairs = append(pairs, Pair{
            SumValue: int64(nums1[i]),
            MinValue: int64(nums2[i]),
        })
    }

    sort.Sort(ByMin(pairs))

    best := &IntHeap{}
    var bestSum int64 = 0

    var answer int64 = 0

    for _, pair := range pairs {
        bestSum += pair.SumValue
        heap.Push(best, pair.SumValue)

        if best.Len() > k {
            min := heap.Pop(best)
            bestSum -= min.(int64)
        }

        if best.Len() == k {
            cur := pair.MinValue * bestSum
            if answer < cur {
                answer = cur
            }
        }
    }

    return answer
}
