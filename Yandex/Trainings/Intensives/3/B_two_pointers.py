n = int(input())
a = list(map(int, input().split()))

max_age = 120

cnts = [0] * (max_age + 1)
for age in a:
    cnts[age] += 1

ans = 0

y = 0
total_count = 0
for x in range(max_age + 1):
    total_count += cnts[x]
    while y <= x and y * 2 <= x + 14:
        total_count -= cnts[y]
        y += 1

    if y <= x:
        ans += cnts[x] * (total_count - 1)  # subtract myself

print(ans)
