from threading import stack_size

mb = 1024 * 1024
stack_size(128 * mb)


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n, need, days = read_ints()
    a = list(read_ints())

    def get_ans():
        a.sort(reverse=True)

        def can(delay):
            total = 0
            for day in range(days):
                index = day % (delay + 1)
                if index < n:
                    total += a[index]

            return total >= need

        left, right = -1, days + 1  # can, can't
        while right - left > 1:
            mid = (left + right) // 2
            if can(mid):
                left = mid
            else:
                right = mid

        return left

    ans = get_ans()
    if ans < 0:
        print("Impossible")
    elif ans >= days:
        print("Infinity")
    else:
        print(ans)


tests = read_int()
for test in range(tests):
    solve_test()
