from collections.abc import Iterator
 
 
def read_line() -> str:
    return input()
 
 
def read_int() -> int:
    return int(read_line())
 
 
def read_tokens() -> list[str]:
    return input().split()
 
 
def read_ints() -> Iterator[int]:
    return map(int, read_tokens())
 
 
def solve():
    n = read_int()
    s = read_line()
    
    q = read_int()
    qp = list(read_ints())
    qd = list(read_ints())
 
    def get_ans() -> bool:
        a = list(map(int, s))
        
        mults = [(i + 1) * (n - i) for i in range(n)]
        
        s0 = sum(mult * v for mult, v in zip(mults, a))
        
        max_n = 10**6
        cache = [None] * (max_n)
        
        def calc_brute(x: int) -> int:
            x_str = str(x)
            
            return sum(
                (i + 1) * (len(x_str) - i) * int(d)
                for i, d in enumerate(x_str)
            )
            
        inf = 10**18
            
        def calc_small(x: int) -> int:
            if x < max_n and cache[x] is not None:
                return cache[x]
                
            if x < max_n:
                cache[x] = inf
                
            x_next = calc_brute(x)
            res_next = calc_small(x_next)
            
            res = min(x, x_next, res_next)
            if x < max_n:
                cache[x] = res
            
            return res
            
        def calc(x: int) -> int:
            return min(x, calc_small(x))
            
        ans = [calc(s0)]
        for p, d in zip(qp, qd):
            cur_d = a[p - 1]
            s0 -= mults[p - 1] * cur_d
            
            a[p - 1] = d
            s0 += mults[p - 1] * d
            
            ans.append(calc(s0))
        
        return ans
        
 
    ans = get_ans()
    print(*ans)
 
 
if __name__ == '__main__':
    solve()
