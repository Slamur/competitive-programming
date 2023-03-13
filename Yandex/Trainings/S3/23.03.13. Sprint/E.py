from collections import deque


with open('input.txt', 'r') as f_in:
    lines = deque(
        line.rstrip()
        for line in f_in.readlines()
    )


def read_line():
    return lines.popleft()


def read_int():
    return int(read_line())


def read_ints():
    return map(int, read_line().split())


h, w = read_ints()

field = [read_line() for _ in range(h)]
field.reverse()

sy, sx = (v - 1 for v in read_ints())
ey, ex = (v - 1 for v in read_ints())

zero = (0 + 1) * 3 + (0 + 1)

cur_q = deque()

inf = h * w + 1

directions = 9
size = h * w * directions

distances = [inf] * size
processed = [False] * size

start = sx * 9 * w + sy * 9 + zero
cur_q.append(start)
distances[start] = 0

while len(cur_q):
    v = cur_q.popleft()

    if processed[v]:
        continue

    processed[v] = True
    distance = distances[v]

    direction = v % 9

    v -= direction

    xy = v // 9
    x = xy // w
    y = xy - x * w

    for to_direction in range(directions):
        if to_direction == zero:
            continue

        if to_direction == direction:
            continue

        if distances[v + to_direction] <= distance + 1:
            continue

        distances[v + to_direction] = distance + 1
        cur_q.append(v + to_direction)

    dx, dy = (direction // 3) - 1, (direction % 3) - 1
    to_x, to_y = x + dx, y + dy
    to_direction = direction

    if to_x < 0 or h <= to_x:
        continue

    if to_y < 0 or w <= to_y:
        continue

    if field[to_x][to_y] == 'X':
        continue

    to_v = to_x * 9 * w + to_y * 9 + to_direction
    if distances[to_v] <= distance:
        continue

    distances[to_v] = distance
    cur_q.appendleft(to_v)

ans = inf

end_v = v = ex * 9 * w + ey * 9
for direction in range(3 * 3):
    ans = min(ans, distances[end_v + direction])

if ans == inf:
    ans = -1

print(ans)
