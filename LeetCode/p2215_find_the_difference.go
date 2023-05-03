func toSet(arr []int) map[int]bool {
    set := make(map[int]bool)
    for _, value := range arr {
        set[value] = true
    }
    return set
}

func findDifference(nums1 []int, nums2 []int) [][]int {
    sets := []map[int]bool{ toSet(nums1), toSet(nums2) }
    
    answer := make([][]int, len(sets))
    for i, set := range sets {
        diff := answer[i]
        otherSet := sets[1 - i]
        for value := range set {
            if !otherSet[value] {
                diff = append(diff, value)
            }
        }
        answer[i] = diff
    }

    return answer
}
