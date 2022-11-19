def read_int():
    return int(input())
    
    
def read_ints():
    return map(int, input().split())


def solve_test():
    n, s = read_ints()
    b = list(read_ints())
    
    def get_ans():
        if len(set(b)) != len(b):
            return False
            
        expected = s + sum(b)
        
        actual = 0
        n = 0
        
        while actual < expected:
            n += 1
            actual += n
            
        return actual == expected and n >= max(b)
        
        
    print("YES" if get_ans() else 'NO')


t = read_int()
for _ in range(t):
    solve_test()
