func checkStraightLine(coordinates [][]int) bool {
    /*
    A = y[1] - y[0]
    B = x[0] - x[1]
    C = -A * x[0] - B * y[0]
    */

    x0, y0 := coordinates[0][0], coordinates[0][1]
    x1, y1 := coordinates[1][0], coordinates[1][1]

    a, b := y1 - y0, x0 - x1
    c := - a * x0 - b * y0

    for _, point := range coordinates {
        x, y := point[0], point[1]
        
        d := a * x + b * y + c
        if d != 0 {
            return false
        }
    }

    return true
}
