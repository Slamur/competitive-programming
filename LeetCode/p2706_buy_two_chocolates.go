func buyChoco(prices []int, money int) int {
    sort.Ints(prices)
    
    total := prices[0] + prices[1]
    if total > money {
        return money
    }
    
    return money - total
}
