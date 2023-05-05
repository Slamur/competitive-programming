import (
    "strings"
)

func maxVowels(s string, k int) int {
    vowels := "aeiou"

    n := len(s)
    isVowel := make([]bool, n)

    for i, letter := range s {
        isVowel[i] = strings.ContainsRune(vowels, letter)
    }
    
    maxVowelsCount := 0

    // (left; right]
    for right, vowelsCount := 0, 0; right < n; right++ {
        left := right - k
        if left >= 0 && isVowel[left] {
            vowelsCount--
        }

        if isVowel[right] {
            vowelsCount++
        }

        if maxVowelsCount < vowelsCount {
            maxVowelsCount = vowelsCount
        }
    }

    return maxVowelsCount
}
