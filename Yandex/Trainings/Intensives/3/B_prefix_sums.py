n = int(input())
a = list(map(int, input().split()))

max_age = 120

cnts = [0] * (max_age + 1)
for age in a:
    cnts[age] += 1

pref = [0] * (max_age + 1)
for age in range(1, max_age + 1):
    pref[age] = pref[age - 1] + cnts[age]

ans = 0
for age in a:
    last_not_invited = (age + 14) // 2
    last_invited = age

    if last_not_invited < last_invited:
        ans += (pref[last_invited] - pref[last_not_invited] - 1)  # subtract myself

print(ans)
