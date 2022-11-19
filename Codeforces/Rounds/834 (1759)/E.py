def read_int():
    return int(input())
    
    
def read_ints():
    return map(int, input().split())
    

def solve_test():
    n, s = read_ints()
    a = list(read_ints())
    a = sorted(a)
    
    def get_ans():
        
        ans = 0
        
        total = 3
        for i in range(total):
            ms = [2] * total
            ms[i] = 3
            
            res = 0
            
            cur = s
            j = 0
            
            for v in a:
                while j < len(ms) and cur <= v:
                    cur *= ms[j]
                    j += 1
                    
                if cur <= v:
                    break
                
                res += 1
                cur += v // 2
            
            ans = max(ans, res)
            
        return ans

    print(get_ans())


t = read_int()
for _ in range(t):
    solve_test()
