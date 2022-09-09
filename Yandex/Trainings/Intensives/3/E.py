def read_ints():
    return map(int, input().split())


n, k = read_ints()
a = list(read_ints())

n += 1
a.append(0)

a.sort(reverse=True)
fictive = a.index(0)

pref = [0] * (n + 1)
for i in range(n):
    pref[i + 1] = pref[i] + a[i]

from collections import defaultdict
cnts = defaultdict(int)
for v in a:
    cnts[v] += 1


def calc(min_power):
    cnt_larger = 0
    total_power = 0

    right = n - 1
    for left in range(n):
        while left < right and a[left] + a[right] <= min_power:
            right -= 1

        if left < right:
            total_power += (pref[right + 1] - pref[left + 1]) + (right - left) * a[left]
            cnt_larger += (right - left)

    cnt_equal = 0
    for i in range(n):
        if i == fictive:
            continue

        need = min_power - a[i]
        if need > a[i]:
            continue

        need_cnt = cnts.get(need, 0)
        if need == a[i]:
            need_cnt -= 1  # remove itself

        cnt_equal += need_cnt

    possible = (k <= cnt_larger + cnt_equal)
    total_power += max(0, k - cnt_larger) * min_power

    return possible, total_power


def can(min_power):
    possible, _ = calc(min_power)
    return possible


min_value, max_value = -10**6 - 1, 10**6 + 1
left, right = min_value * 2 - 1, max_value * 2 + 1
while right - left > 1:
    mid = (left + right) // 2
    if can(mid):
        left = mid
    else:
        right = mid

_, total_power = calc(left)
print(total_power)
