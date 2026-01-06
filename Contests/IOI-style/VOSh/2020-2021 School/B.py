def read_ints():
    # return list(map(int, input().split()))
    return [int(i) for i in input().split()]


def read_int():
    return read_ints()[0]


def get_answer(cruassans, eclers):
    d = 1 * 1 - 2 * 2

    d12 = cruassans - 2 * eclers
    d21 = eclers - 2 * cruassans

    no_answer = [-1]

    if d12 % d != 0 or d21 % d != 0:
        return no_answer

    b12 = d12 // d
    b21 = d21 // d

    if b12 < 0 or b21 < 0:
        return no_answer

    return [b21, b12]


def solve():
    cruassans = read_int()
    eclers = read_int()

    answer = get_answer(cruassans, eclers)
    print(*answer, sep=' ')


solve()
