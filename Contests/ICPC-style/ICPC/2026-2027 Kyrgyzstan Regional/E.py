def solve():
    s = input()
 
    def get_ans() -> tuple[int, int]:
        n = len(s)
 
        closed = [None] * n
        open_stack = []
        for i, ch in enumerate(s):
            if ch == '{':
                open_stack.append(i)
            elif ch == '}':
                closed[open_stack.pop()] = i
        
        def parse(start: int, end: int) -> tuple[int, int, int]:
            w = 0
            max_num_h, max_den_h = 0, 0
            
            i = start
            
            while i < end:
                ch = s[i]
                if ch == '{':
                    num_w, num_h = parse(i + 1, closed[i])
                    
                    den_open = closed[i] + 2
                    den_w, den_h = parse(den_open + 1, closed[den_open])
                    
                    frac_w = max(num_w, den_w) + 2
                    
                    w += frac_w
                    max_num_h = max(max_num_h, num_h)
                    max_den_h = max(max_den_h, den_h)
                    
                    i = closed[den_open]
                else:
                    w += 1
                    
                i += 1
                
            return w, 1 + max_num_h + max_den_h
        
        return parse(0, n)
 
    width, height = get_ans()
    print(width, height)
 
 
if __name__ == '__main__':
    solve()
