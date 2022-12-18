def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n = read_int()
    s = input()

    s = s[1:]
    ones = s.count('1')

    plus_count = ones // 2
    minus_count = ones - plus_count

    ans = []
    for v in s:
        if v == '0':
            ans.append('+')
        else:
            if plus_count > 0:
                plus_count -= 1
                ans.append('+')
            else:
                ans.append('-')

    print(''.join(ans))


t = read_int()
for _ in range(t):
    solve_test()
