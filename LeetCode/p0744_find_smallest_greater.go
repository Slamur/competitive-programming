func nextGreatestLetter(letters []byte, target byte) byte {
    pos := sort.Search(len(letters), func(index int) bool { 
        return letters[index] > target 
    })

    if pos == len(letters) {
        pos = 0
    }

    return letters[pos]
}
