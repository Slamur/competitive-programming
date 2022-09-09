n = int(input())
a = list(map(int, input().split()))

max_age = 120

cnts = [0] * (max_age + 1)
for age in a:
    cnts[age] += 1

ans = 0

for x in range(max_age + 1):
    for y in range(max_age + 1):
        not_invited = False
        not_invited |= y * 2 <= x + 14
        not_invited |= y > x
        not_invited |= y > 100 > x
        if not not_invited:
            ans += cnts[x] * (cnts[y] - (1 if x == y else 0))

print(ans)
