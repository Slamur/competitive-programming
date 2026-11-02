import random
 
CIRCLE_LENGTH = 10 ** 9
MAX_PROBES = 30
 
 
def read_line() -> str:
    return input()
 
 
def read_int() -> int:
    return int(read_line())
 
 
def read_tokens() -> list[str]:
    return read_line().split()
 
 
def shift(cell: int, delta: int) -> int:
    return (cell + delta) % CIRCLE_LENGTH
 
 
def circle_distance(first: int, second: int) -> int:
    difference = abs(first - second)
    return min(difference, CIRCLE_LENGTH - difference)
 
 
def ask(cell: int) -> tuple[bool, int]:
    print('?', cell + 1, flush=True)
    verdict, distance = read_tokens()
    return verdict == 'YES', int(distance)
 
 
def answer(cell: int) -> None:
    print('!', cell + 1, flush=True)
 
 
def solve():
    n = read_int()
    
    random.seed(n + 123)
 
    def guess() -> None:
        alive = n
        
        def rand_start() -> int:
            return random.randrange(0, CIRCLE_LENGTH)
        
        cur = rand_start()
        last, last_distance = None, None
        
        yes_streak = 0
        max_yes_streak = 2
        
        while True:
            exploded, distance = ask(cur)
            if not exploded:
                if last is not None:
                    mirror = shift(last, -last_distance)
                    answer(mirror)
                    return
                    
            if distance == CIRCLE_LENGTH // 2:
                answer(shift(cur, distance))
                return
            
            if exploded:
                alive -= 1
                yes_streak += 1
                
            last, last_distance = cur, distance
            cur = shift(cur, distance)
 
            if alive == 1:
                break
                
            if yes_streak >= max_yes_streak:
                cur = rand_start()
                last, last_distance = None, None
                yes_streak = 0
                continue
            
        # for 1
        c1, c2 = shift(last, -last_distance), shift(last, last_distance)
        last_c = {c1, c2}
        
        cur = c2
        while True:
            cur = shift(cur, 1)
            if cur in (c1, c2):
                continue
            
            if shift(cur, CIRCLE_LENGTH // 2) == last:
                continue
            
            _, distance = ask(cur)
            cur_c1, cur_c2 = shift(cur, -distance), shift(cur, distance)
            
            cur_c = {cur_c1, cur_c2}
            
            only_c = last_c & cur_c
            for c in only_c:
                answer(c)
                return
 
    guess()
 
 
if __name__ == '__main__':
    solve()
