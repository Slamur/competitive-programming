read_line = input 


def read_token(parse=str):
    return parse(read_line())


def read_tokens(parse=str):
    return map(parse, read_line().split())


def yes_no(yes, yes_str='YES', no_str='NO'):
    print(yes_str if yes else no_str)
    return yes


def solve():
    s = read_line()

    def get_ans():
        red, blue = 'R', 'B'

        n = len(s)

        def calc(balls):

            red_no_blue = []
            for i in range(n):
                if balls[i] == red and (i + 1 == n or balls[i + 1] != blue):
                    red_no_blue.append(i)

            return red_no_blue

        red_no_blue = calc(s)

        if len(red_no_blue) == 0:
            return True
        
        bad_red = red_no_blue[0]

        for l_candidate in range(bad_red - 3, bad_red + 4):
            if l_candidate not in range(0, n):
                continue
            
            r_candidate = l_candidate + 1
            if r_candidate not in range(0, n):
                continue

            new_balls = s[:l_candidate] + s[r_candidate] + s[l_candidate] + s[r_candidate + 1:]
            if len(calc(new_balls)) == 0:
                return True

        return False
    
    ans = get_ans()
    yes_no(ans)


if __name__ == '__main__':
    solve()
