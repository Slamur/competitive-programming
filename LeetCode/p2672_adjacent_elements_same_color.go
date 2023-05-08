func colorTheArray(n int, queries [][]int) []int {
    colors := make([]int, n)

    numSegs := 0
    numColors := 0

    q := len(queries)
    answers := make([]int, q)

    for i, query := range queries {
        index, color := query[0], query[1]

        if colors[index] == 0 {
            numColors++
            numSegs++
        } else {
            if index > 0 && colors[index - 1] == colors[index] {
                numSegs++
            }
            if index + 1 < n && colors[index + 1] == colors[index] {
                numSegs++
            }
        }

        colors[index] = color

        if index > 0 && colors[index - 1] == colors[index] {
            numSegs--
        }

        if index + 1 < n && colors[index + 1] == colors[index] {
            numSegs--
        }

        answers[i] = numColors - numSegs
    }

    return answers
}
