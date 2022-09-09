MINUTES_IN_HOUR = 60
HOURS_IN_DAY = 24
MINUTES_IN_DAY = MINUTES_IN_HOUR * HOURS_IN_DAY


def parse_time(time_str):
    h, m = map(int, time_str.split(":"))
    return h * MINUTES_IN_HOUR + m


n = int(input())
a = list(map(parse_time, input().split()))

a.sort()
a.append(a[0] + MINUTES_IN_DAY)

ans = MINUTES_IN_DAY
for i in range(n):
    ans = min(ans, a[i + 1] - a[i])
print(ans)
