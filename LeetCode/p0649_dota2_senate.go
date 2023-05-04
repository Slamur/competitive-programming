func predictPartyVictory(senate string) string {
    n := len(senate)

    radiant := make([]int, 0)
    dire := make([]int, 0)

    for i, letter := range senate {
        if 'R' == letter {
            radiant = append(radiant, i)
        } else {
            dire = append(dire, i)
        }
    }

    ir, id := 0, 0

    for ; ir < len(radiant) && id < len(dire); {
        if radiant[ir] < dire[id] {
            radiant = append(radiant, radiant[ir] + n)
        } else {
            dire = append(dire, dire[id] + n)
        }
        ir++
        id++
    }
    
    if ir == len(radiant) {
        return "Dire"
    } else {
        return "Radiant"
    }
}
