def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n = read_int()
lectures = [tuple(read_ints()) for _ in range(n)]

segments = sorted((end, start) for start, end in lectures)

ans = 0

last_end = -1
for end, start in segments:
    if last_end <= start:
        ans += 1
        last_end = end

print(ans)