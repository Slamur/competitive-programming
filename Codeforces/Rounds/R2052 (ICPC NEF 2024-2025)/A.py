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
    n = read_token(int)
    finish_order = list(read_tokens(int))

    def get_ans():
        answer = []

        current_order = list(range(1, n + 1))

        while finish_order:
            back = finish_order.pop()

            back_pos = current_order.index(back)
            for front_pos in range(back_pos - 1, -1, -1):
                front = current_order[front_pos]
                answer.append([back, front])

            current_order.remove(back)

            for front in current_order:
                answer.append([front, back])

        return answer

    ans = get_ans()
    print(len(ans))

    print('\n'.join(
        f"{back} {front}"
        for back, front in ans
    ))


def solve():
    t = 1
    # t = read_token(int)

    for _ in range(t):
        solve_test()


if __name__ == "__main__":
    solve()
