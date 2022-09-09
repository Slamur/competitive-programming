def read_ints():
    return map(int, input().split())


n, k = read_ints()
xs = list(read_ints())


def can(min_dist):
    cnt = 0
    last = xs[0] - min_dist
    for x in xs:
        if last + min_dist <= x:
            cnt += 1
            last = x

    return cnt >= k


left, right = 0, xs[-1] - xs[0] + 1
while right - left > 1:
    mid = (left + right) // 2
    if can(mid):
        left = mid
    else:
        right = mid

print(left)