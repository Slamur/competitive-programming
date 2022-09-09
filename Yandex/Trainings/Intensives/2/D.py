def read_ints():
    return map(int, input().split())


n = int(input())
a = list(read_ints())


from collections import defaultdict
cnts = defaultdict(int)

for v in a:
    cnts[v] += 1

_, ans_v = max((cnt, v) for v, cnt in cnts.items())
print(ans_v)
