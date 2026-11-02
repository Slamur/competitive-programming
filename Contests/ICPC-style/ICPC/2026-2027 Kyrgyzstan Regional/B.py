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
 
    def get_ans() -> tuple[int, int]:
        total = 3 * n
        
        small, large = 6, 8
        
        def ceil(a: int, b: int) -> int:
            return (a - 1) // b + 1
        
        if total < 15 or total == 18:
            return ceil(total, small), 0
            
        return 0, ceil(total, large)
 
    ans_6, ans_8 = get_ans()
    print(ans_6, ans_8)
 
 
if __name__ == '__main__':
    solve()
