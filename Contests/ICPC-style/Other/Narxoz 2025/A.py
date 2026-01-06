read_line = input 


def read_token(parse=str):
    return parse(read_line())


def read_tokens(parse=str):
    return map(parse, read_line().split())


def yes_no(yes, yes_str='YES', no_str='NO'):
    print(yes_str if yes else no_str)
    return yes


def solve():
    n, k = read_tokens(int)
    a = list(read_tokens(int))

    def get_ans():
        free = set(range(1, n + 1)) - set(a)
        return list(sorted(free))
    
    ans = get_ans()
    print(*ans)


if __name__ == '__main__':
    solve()
