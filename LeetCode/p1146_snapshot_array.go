type SnapshotArray struct {
    traces [][][2]int
    version int
}


func Constructor(length int) SnapshotArray {
    traces := make([][][2]int, length)
    for i := range traces {
        traces[i] = append(traces[i], [2]int{-1, 0})
    }

    return SnapshotArray {
        traces: traces,
        version: 0,
    }
}


func (this *SnapshotArray) Set(index int, val int)  {
    this.traces[index] = append(this.traces[index], [2]int{this.version, val})
}


func (this *SnapshotArray) Snap() int {
    this.version++
    return this.version - 1
}


func (this *SnapshotArray) Get(index int, snap_id int) int {
    trace := this.traces[index]

    pos := sort.Search(len(trace), func(i int) bool {
        return trace[i][0] > snap_id
    })
    return trace[pos - 1][1]
}


/**
 * Your SnapshotArray object will be instantiated and called as such:
 * obj := Constructor(length);
 * obj.Set(index,val);
 * param_2 := obj.Snap();
 * param_3 := obj.Get(index,snap_id);
 */
