def read_ints():
    # return list(map(int, input().split()))
    return [int(i) for i in input().split()]


def read_int():
    return read_ints()[0]


def get_answer(n, columns):
    columns_new = [-1] * n
    for row in range(n):
        column = columns[row]

        row_new = column
        column_new = n - 1 - row

        columns_new[row_new] = column_new

    return columns_new


def solve():
    n = read_int()
    columns = [read_int() - 1 for _ in range(n)]

    columns_new = get_answer(n, columns)

    answer_strings = [str(answer + 1) for answer in columns_new]
    print('\n'.join(answer_strings))


solve()
