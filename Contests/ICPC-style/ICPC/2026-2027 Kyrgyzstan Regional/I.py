def read_line() -> str:
    return input()
 
 
def read_int() -> int:
    return int(read_line())
 
 
def solve():
    n = read_int()
 
    def get_ans() -> list[list[int]]:
        size = 2**n
        
        ans = [[None] * size for _ in range(size)]
        
        up, down, left, right = range(4)
        
        def inc(sr: int, sc: int, size: int, start: int):
            for r in range(sr, sr + size):
                for c in range(sc, sc + size):
                    ans[r][c] += start
                    
        def mirror_horz(sr: int, sc: int, size: int):
            mr, er = sr + size // 2, sr + size
            total = size ** 2
            
            for c in range(sc, sc + size):
                for r in range(sr, mr):
                    mirror_r = er - 1 - (r - sr)
                    ans[mirror_r][c] = total - 1- ans[r][c]
        
        def mirror_vert(sr: int, sc: int, size: int):
            mc, ec = sc + size // 2, sc + size
            total = size ** 2
            
            for r in range(sr, sr + size):
                for c in range(sc, mc):
                    mirror_c = ec - 1 - (c - sc)
                    ans[r][mirror_c] = total - 1 - ans[r][c]
        
        def gen(start: int, sr: int, sc: int, size: int, dir: int):
            if size == 1:
                ans[sr][sc] = start
                return
        
            half = size // 2    
            
            if dir == down:
                gen(0, sr, sc, half, right)
                gen(half**2, sr + half, sc, half, down)
                mirror_vert(sr, sc, size)
            
            if dir == right:
                gen(0, sr, sc, half, down)
                gen(half**2, sr, sc + half, half, right)
                mirror_horz(sr, sc, size)
                
            inc(sr, sc, size, start)
        
        gen(1, 0, 0, size, down)
        
        return ans
            
    ans = get_ans()
    ans_str = '\n'.join(' '.join(map(str, row)) for row in ans)
    print(ans_str)
 
 
if __name__ == '__main__':
    solve()
