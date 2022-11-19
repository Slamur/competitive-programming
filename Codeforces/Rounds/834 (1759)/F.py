def read_int():
    return int(input())
    
    
def read_ints():
    return map(int, input().split())
    

def solve_test():
    n, p = read_ints()
    x = list(read_ints())
    
    
    def get_ans():
        k = x[-1]
        
        seen = set(x)
        
        ld = 0
        while ld in seen and ld < k:
            ld += 1
            
        md = p - 1
        while md in seen and md > k:
            md -= 1
            
        if ld == k:
            return md - k
            
        # x += p - k
        last_not_max = n - 2
        while last_not_max >= 0 and x[last_not_max] == p - 1:
            last_not_max -= 1
            
        if last_not_max < 0:
            x.insert(0, 0)
            last_not_max += 1
            
        x[last_not_max] += 1
        for i in range(last_not_max + 1, len(x)):
            x[i] = 0
        
        for d in x:
            seen.add(d)
            
        nd = k - 1
        while nd in seen and nd >= 0:
            nd -= 1
        
        return p - k + max(0, nd)

    print(get_ans())


t = read_int()
for _ in range(t):
    solve_test()
