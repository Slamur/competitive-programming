func minFlips(a int, b int, c int) int {
    ans := 0

    for a > 0 || b > 0 || c > 0 {
        aBit, bBit, cBit := a & 1, b & 1, c & 1
        if cBit == 0 {
            ans += aBit + bBit
        } else {
            if aBit + bBit == 0 {
                ans++
            }
        }

        a >>= 1
        b >>= 1
        c >>= 1
    }

    return ans
}
