import heapq
import sys
from collections import *
import math


def read_line():
    return sys.stdin.readline().strip()


def read_token(transform=str):
    return transform(read_line())


def read_tokens(transform=str):
    return map(transform, read_line().split())


def solve_test():
    expression = list(read_line())

    def get_ans():
        def calc(expression, start_pos, end_pos):
            no_ans = None

            res = 0

            last_num = []

            last_sign = 1
            was_sign = True

            for pos in range(start_pos, end_pos + 1):
                ch = '+' if pos == end_pos else expression[pos]

                is_sign = ch in '+-'
                if is_sign and was_sign:
                    return no_ans

                if is_sign:
                    # some number finished
                    if len(last_num) > 1 and last_num[0] == '0':
                        return no_ans

                    if len(last_num) > 10:
                        return no_ans

                    res += last_sign * int(''.join(last_num))

                    last_num = []
                    last_sign = 1 if ch == '+' else -1
                else:
                    last_num.append(ch)

                was_sign = is_sign

            return res

        def is_valid(expression):
            eq_pos = expression.index('=')

            if eq_pos == 0 or eq_pos == len(expression) - 1:
                return False

            left_res = calc(expression, 0, eq_pos)
            if left_res is None:
                return False

            right_res = calc(expression, eq_pos + 1, len(expression))
            if right_res is None:
                return False

            return left_res == right_res

        already_correct = "Correct"
        impossible = "Impossible"

        if is_valid(expression):
            return already_correct

        for moved_pos in range(len(expression)):
            if not expression[moved_pos].isdigit():
                continue

            moved_digit = expression[moved_pos]
            moved_expression = expression[:moved_pos] + expression[moved_pos + 1:]

            for insert_before_pos in range(len(moved_expression) + 1):
                inserted_expression = moved_expression[:insert_before_pos] + [moved_digit] + moved_expression[insert_before_pos:]
                if is_valid(inserted_expression):
                    return inserted_expression

        return impossible

    ans = get_ans()
    print(''.join(ans))


def solve():
    t = 1
    # t = read_token(int)

    for _ in range(t):
        solve_test()


if __name__ == "__main__":
    solve()
