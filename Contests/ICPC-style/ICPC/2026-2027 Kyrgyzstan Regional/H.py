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
    n, k = read_ints()
    a = list(read_ints())
 
    def get_ans() -> list[int]:
        def min_shift(x: int) -> int:
            x_str = str(x)
            xx_str = x_str + x_str
            
            d = len(x_str)
            
            best_str = min(
                xx_str[i:i+d]
                for i in range(d)
            )
            
            return int(best_str)
        
        best = [min_shift(x) for x in a]
        
        best_deltas = [
            (x - best_x, i)
            for i, (x, best_x) in enumerate(zip(a, best))
        ]
        
        best_deltas.sort(reverse=True)
        
        ans = list(a)
        for delta, index in best_deltas[:k]:
            ans[index] -= delta
        return ans
 
    ans = get_ans()
    print(*ans)
 
 
if __name__ == '__main__':
    solve()
