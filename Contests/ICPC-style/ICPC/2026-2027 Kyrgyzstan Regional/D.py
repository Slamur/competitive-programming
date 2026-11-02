from collections.abc import Iterator
 
 
def read_tokens() -> list[str]:
    return input().split()
 
 
def read_ints() -> Iterator[int]:
    return map(int, read_tokens())
 
 
def is_leap(year: int) -> bool:
    return year % 400 == 0 or (year % 4 == 0 and year % 100 != 0)
 
 
def days_in_month(month: int, year: int) -> int:
    if month == 2:
        return 29 if is_leap(year) else 28
    if month in (4, 6, 9, 11):
        return 30
    return 31
 
 
def solve():
    m, y = read_ints()
    d, m2, y2 = read_ints()
 
    def get_ans() -> int:
        res = 0
        
        def delta(m_start: int, m_end: int, year: int) -> int:
            return sum(days_in_month(month, year) for month in range(m_start, m_end))
        
        if y < y2:
            res += delta(m, 12 + 1, y)
            
            for year in range(y + 1, y2):
                res += 365 + int(is_leap(year))
            
            res += delta(1, m2, y2)
        else:
            res += delta(m, m2, y)
        
        res += d
        
        return res
 
    ans = get_ans()
    print(ans)
 
 
if __name__ == '__main__':
    solve()
