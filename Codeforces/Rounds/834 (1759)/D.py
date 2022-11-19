def read_int():
    return int(input())
    
    
def read_ints():
    return map(int, input().split())
    
    
def calc(n, p):
    res = 0
    while n % p == 0:
        res += 1
        n //= p
        
    return res


def solve_test():
    n, m = read_ints()
    
    def get_ans():
        p2 = calc(n, 2)
        p5 = calc(n, 5)
        
        k = 1
        while p2 < p5 and k * 2 <= m:
            k *= 2
            p2 += 1
        
        while p5 < p2 and k * 5 <= m:
            k *= 5
            p5 += 1
            
        while k * 10 <= m:
            k *= 10
        
        ans_k = m - m % k
        
        return n * ans_k

    print(get_ans())


t = read_int()
for _ in range(t):
    solve_test()
