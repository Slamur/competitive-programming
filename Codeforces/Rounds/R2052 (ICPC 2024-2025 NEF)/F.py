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

    rows = [
        read_line()
        for _ in range(2)
    ]

    def get_ans():
        rows_cnt = len(rows)
        states_cnt = 1 << rows_cnt

        none, top, bottom, both = range(states_cnt)

        dp = [
            [0] * states_cnt
            for _ in range(2)
        ]

        dp[0][both] = 1

        inf = 2

        for i in range(n):
            prev_dp = dp[i % 2]
            cur_dp = dp[1 - i % 2]

            for state in range(states_cnt):
                cur_dp[state] = 0

            has_top = rows[0][i] == '#'
            has_bottom = rows[1][i] == '#'

            if not has_top and not has_bottom:
                # 00
                cur_dp[none] += prev_dp[both]

                cur_dp[both] += prev_dp[none]
                cur_dp[both] += prev_dp[both]

                cur_dp[top] += prev_dp[bottom]
                cur_dp[bottom] += prev_dp[top]

            if not has_top and has_bottom:
                # 01
                cur_dp[both] += prev_dp[bottom]
                cur_dp[bottom] += prev_dp[both]

            if has_top and not has_bottom:
                # 10
                cur_dp[both] += prev_dp[top]
                cur_dp[top] += prev_dp[both]

            if has_top and has_bottom:
                # 11
                cur_dp[both] += prev_dp[both]

            for state in range(states_cnt):
                cur_dp[state] = min(cur_dp[state], inf)

        return dp[n % 2][both]

    ans = get_ans()
    print(['None', 'Unique', 'Multiple'][ans])


def solve():
    t = 1
    t = read_token(int)

    for _ in range(t):
        solve_test()


if __name__ == "__main__":
    solve()
