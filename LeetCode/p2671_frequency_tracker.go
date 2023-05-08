type FrequencyTracker struct {
    valueToFreq map[int]int
    freqToCount map[int]int
}


func Constructor() FrequencyTracker {
    return FrequencyTracker {
        valueToFreq: make(map[int]int),
        freqToCount: make(map[int]int),
    }
}


func (this *FrequencyTracker) Add(number int)  {
    oldFreq := this.valueToFreq[number]
    if oldFreq > 0 {
        this.freqToCount[oldFreq]--
    }

    this.valueToFreq[number]++
    this.freqToCount[oldFreq + 1]++
}


func (this *FrequencyTracker) DeleteOne(number int)  {
    oldFreq := this.valueToFreq[number]
    if oldFreq == 0 {
        return
    }

    this.freqToCount[oldFreq]--
    this.valueToFreq[number]--

    if oldFreq > 1 {
        this.freqToCount[oldFreq - 1]++
    }
}


func (this *FrequencyTracker) HasFrequency(frequency int) bool {
    return this.freqToCount[frequency] > 0
}


/**
 * Your FrequencyTracker object will be instantiated and called as such:
 * obj := Constructor();
 * obj.Add(number);
 * obj.DeleteOne(number);
 * param_3 := obj.HasFrequency(frequency);
 */
