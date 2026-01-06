import heapq
import sys
from collections import *
import math
import bisect


def read_line():
    return sys.stdin.readline().strip()


def read_token(transform=str):
    return transform(read_line())


def read_tokens(transform=str):
    return map(transform, read_line().split())


def solve_test():
    tasks_cnt, episodes_cnt, queries_cnt = read_tokens(int)

    task_durations = list(read_tokens(int))
    task_deadlines = list(read_tokens(int))

    episode_durations = list(read_tokens(int))

    queries = list(read_tokens(int))

    def get_ans():
        tasks = list(zip(task_deadlines, task_durations))
        tasks.sort(reverse=True)

        inf_time = 10**100

        # start, duration
        task_segments = [
            (inf_time, 0), # death deadline
        ]

        finish_at_most = inf_time
        for deadline, duration in tasks:
            finish = min(finish_at_most, deadline)
            start = finish - duration

            task_segments.append((start, duration))
            finish_at_most = start

        task_segments.reverse()

        first_free_time = 0
        next_task_to_complete = 0

        task_type, episode_type = range(2)

        event_finishes = [
            [first_free_time, task_type], # start of prefix sums
        ]

        for episode_duration in episode_durations:
            while True:
                next_task_start, next_task_duration = task_segments[next_task_to_complete]
                if next_task_start - first_free_time >= episode_duration:
                    break

                event_finishes.append([next_task_duration, task_type])

                first_free_time += next_task_duration
                next_task_to_complete += 1

            event_finishes.append([episode_duration, episode_type])
            first_free_time += episode_duration

        for i in range(1, len(event_finishes)):
            event_finishes[i][0] += event_finishes[i - 1][0]
            event_finishes[i][1] += event_finishes[i - 1][1]

        def calc_answer(query_time):
            query_finish = [query_time + 1, -1]

            first_finish_gr = bisect.bisect(event_finishes, query_finish)
            last_finish_le = first_finish_gr - 1

            return event_finishes[last_finish_le][1]

        return [
            calc_answer(query)
            for query in queries
        ]

    ans = get_ans()
    print(' '.join(
        map(str, ans)
    ))


def solve():
    t = 1
    t = read_token(int)

    for _ in range(t):
        solve_test()


if __name__ == "__main__":
    solve()
