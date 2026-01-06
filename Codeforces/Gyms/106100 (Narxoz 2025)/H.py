read_line = input 


def read_token(parse=str):
    return parse(read_line())


def read_tokens(parse=str):
    return map(parse, read_line().split())


def yes_no(yes, yes_str='YES', no_str='NO'):
    print(yes_str if yes else no_str)
    return yes


def solve():
    a, b = read_tokens(int)

    def get_ans():
        def is_prime(x):
            if x < 2:
                return False
            
            d = 2
            while d * d <= x:
                if x % d == 0:
                    return False
                
                d += 1
                
            return True
        
        return (a - b) == 1 and is_prime(a + b)
    
    ans = get_ans()
    yes_no(ans)


if __name__ == '__main__':
    solve()
