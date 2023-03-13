from collections import deque


with open('input.txt', 'r') as f_in:
    lines = deque(
        line.rstrip()
        for line in f_in.readlines()
    )


def read_line():
    return lines.popleft()


def read_int():
    return int(read_line())


def read_ints():
    return map(int, read_line().split())


n = read_int()
times = [tuple(read_ints()) for _ in range(n)]

max_time = 0
for index in range(2):
    max_time = max(max_time, sum(time[index] for time in times))

inf = max_time + 1

dp = [[inf] * (max_time + 1) for _ in range(n + 1)]

dp[0][0] = 0
for i, time in enumerate(times):
    first, second = time

    prev_dp = dp[i]
    cur_dp= dp[i + 1]

    for ft in range(max_time + 1):
        cur_dp[ft] = prev_dp[ft] + second

        if ft >= first:
            cur_dp[ft] = min(cur_dp[ft], prev_dp[ft - first])

ans_dp = dp[n]

answers = [max(ft, st) for ft, st in enumerate(ans_dp)]

ans = min(answers)

ft = answers.index(ans)
st = ans_dp[ft]

path = []
for i in range(n - 1, -1, -1):
    first, second = times[i]

    step = -1
    if dp[i][ft] + second == st:
        st -= second
        step = 2
    else:
        ft -= first
        step = 1

    path.append(step)

path.reverse()
print(*path)

