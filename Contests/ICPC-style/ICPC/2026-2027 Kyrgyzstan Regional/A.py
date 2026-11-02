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
 
    def get_ans() -> bool:
        while n % 2 == 0:
            n //= 2

        return n == 1
 
    ans = get_ans()
    print('YES' if ans else 'NO')
 
 
if __name__ == '__main__':
    solve()
