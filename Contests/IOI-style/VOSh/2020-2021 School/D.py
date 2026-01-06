def read_ints():
    # return list(map(int, input().split()))
    return [int(i) for i in input().split()]


def read_int():
    return read_ints()[0]


import math


# возвращаем res * res <= x
def int_sqrt(x):
    res = int(math.sqrt(x))

    while res * res > x:
        res -= 1

    while (res + 1) * (res + 1) <= x:
        res += 1

    return res


def solve():
    n = read_int() - 1

    left_square_root = int_sqrt(n)
    left_square = left_square_root * left_square_root

    right_square_root = left_square_root + 1
    right_square = right_square_root * right_square_root

    delta = n - left_square

    row = 0
    column = left_square_root

    go_down = min(left_square_root, delta)

    row += go_down
    delta -= go_down

    go_left = min(left_square_root, delta)

    column -= go_left

    if left_square_root % 2 == 0:
        row, column = column, row

    print(row + 1, column + 1)


solve()
