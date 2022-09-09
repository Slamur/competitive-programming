def read_set():
    input()
    return set(map(int, input().split()))


total = 3
min_need = 2
sets = [read_set() for _ in range(total)]

from collections import defaultdict
cnts = defaultdict(int)

for number_set in sets:
    for value in number_set:
        cnts[value] += 1


ans = []
for value, cnt in cnts.items():
    if cnt >= min_need:
        ans.append(value)

ans.sort()
print(*ans)
