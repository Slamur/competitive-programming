type MyHashSet struct {
    capacity int
    buckets [][]int
}


func Constructor() MyHashSet {
    maxOperations := 10 * 1000
    capacityBits := 0
    for ; (1 << capacityBits) < maxOperations; capacityBits++ { }
    
    capacity := (1 << capacityBits)

    return MyHashSet {
        capacity: capacity,
        buckets: make([][]int, capacity),
    }
}

func (this *MyHashSet) find(key int) (*[]int, int) {
    hash := key & (this.capacity - 1)

    bucket := &(this.buckets[hash])
    position := -1

    for index, value := range *bucket {
        if value == key {
            position = index
            break
        }
    }

    return bucket, position
}

func (this *MyHashSet) Add(key int)  {
    bucket, position := this.find(key)
    if position == -1 {
        (*bucket) = append(*bucket, key)
    }
}


func (this *MyHashSet) Remove(key int)  {
    bucket, position := this.find(key)
    if position != -1 {
        (*bucket) = append((*bucket)[:position], (*bucket)[position+1:]...)
    }
}


func (this *MyHashSet) Contains(key int) bool {
    _, position := this.find(key)
    return position != -1
}


/**
 * Your MyHashSet object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Add(key);
 * obj.Remove(key);
 * param_3 := obj.Contains(key);
 */
