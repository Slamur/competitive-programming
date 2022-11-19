def read_int():
    return int(input())
    
    
def read_ints():
    return map(int, input().split())


def solve_test():
    l, r, x = read_ints()
    a, b = read_ints()
    
    def get_ans():
        ids = [a, b, l, r]
        
        from collections import defaultdict
        g = defaultdict(list)
        
        for f in ids:
            for t in ids:
                if abs(f - t) >= x:
                    g[f].append(t)
                    
        d = defaultdict(lambda: -1)
        
        from collections import deque
        q = deque()
        
        d[a] = 0
        q.append(a)
        
        while len(q) > 0:
            v = q.pop()
            for v_to in g[v]:
                if d[v_to] == -1:
                    d[v_to] = d[v] + 1
                    q.append(v_to)
        
        return d[b]
        
    print(get_ans())


t = read_int()
for _ in range(t):
    solve_test()
