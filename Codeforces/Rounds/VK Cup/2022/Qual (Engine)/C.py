def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n = read_int()
    a = list(read_ints())

    def get_ans():
        moving = 1
        pushed = 2
        fixed = 3

        modes = dict()

        for x in a:
            if x not in modes:
                modes[x] = moving
            elif modes[x] == moving or modes[x] == pushed:
                modes[x] = fixed
                modes[x + 1] = pushed

        events = list(modes.items())

        events.sort()

        max_segment_length = 0

        last_moving = -1
        last = -1

        prev_moving = 0
        cur_moving = 0

        cur = 0

        for x, mode in events:
            if last < x - 2:
                prev_moving = 0

            if last == x - 2:
                prev_moving = cur_moving

            if last_moving < x - 1:
                cur_moving = 0

            if last < x - 1:
                cur = 0

            if mode == moving:
                cur_moving += 1
                last_moving = x

            cur += min(1, x - last)
            last = x

            max_segment_length = max(max_segment_length, prev_moving + cur)

        return max_segment_length

    ans = get_ans()
    print(ans)


def solve():
    tests = read_int()
    for test in range(tests):
        solve_test()


if __name__ == '__main__':
    solve()
