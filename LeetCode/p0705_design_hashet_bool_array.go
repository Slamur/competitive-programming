type MyHashSet struct {
    used []bool
}


func Constructor() MyHashSet {
    maxKey := 1000 * 1000
    return MyHashSet {
        used: make([]bool, maxKey + 1),
    }
}


func (this *MyHashSet) Add(key int)  {
    this.used[key] = true
}


func (this *MyHashSet) Remove(key int)  {
    this.used[key] = false
}


func (this *MyHashSet) Contains(key int) bool {
    return this.used[key]
}


/**
 * Your MyHashSet object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Add(key);
 * obj.Remove(key);
 * param_3 := obj.Contains(key);
 */
