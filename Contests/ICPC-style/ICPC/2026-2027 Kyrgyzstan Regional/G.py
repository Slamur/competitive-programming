from collections.abc import Iterator
 
 
def read_line() -> str:
    return input()
 
 
def read_tokens() -> list[str]:
    return input().split()
 
 
def read_ints() -> Iterator[int]:
    return map(int, read_tokens())
 
 
def solve():
    n, k, q = read_ints()
    positions = list(read_ints())
 
    binom = [[0] * (n + 1) for _ in range(n + 1)]
    for r in range(n + 1):
        binom[r][0] = 1
        for w in range(1, r + 1):
            binom[r][w] = binom[r - 1][w - 1] + binom[r - 1][w]
 
    block_size = 1 << (n - k)
    
    def get_ans(p: int) -> int:
        p -= 1
        p //= block_size
        
        wins = k
        while p >= binom[k][wins]:
            p -= binom[k][wins]
            wins -= 1
                
        ans = 0
        
        for cur in range(k, 0, -1):
            ans <<= 1
            if wins == 0:
                continue
            
            if p < binom[cur - 1][wins - 1]:
                ans |= 1
                wins -= 1
            else:
                p -= binom[cur - 1][wins - 1]
        
        return ans
        
        
    answers = [get_ans(p) for p in positions]
    print(*answers)
 
 
if __name__ == '__main__':
    solve()
