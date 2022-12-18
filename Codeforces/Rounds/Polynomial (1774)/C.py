def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n = read_int()
    s = list(map(int, input()))

    left = 0
    right = 0

    ans = [0] * (n - 1)
    last = -1
    last_ans = 1
    for i, v in enumerate(s):
        if i > 0 and last != v:
            ans[i] = left + right + 1
            last_ans = ans[i]
        else:
            ans[i] = last_ans

        if v == 0:
            right += 1
        else:
            left += 1

        last = v

    print(" ".join(map(str, ans)))


t = read_int()
for _ in range(t):
    solve_test()
