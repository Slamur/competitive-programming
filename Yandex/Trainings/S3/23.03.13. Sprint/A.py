from collections import deque, defaultdict


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


q = read_int()

train = deque()
counts = defaultdict(int)

ADD_RIGHT, DELETE_RIGHT, GET_COUNT = 'add', 'delete', 'get'

answers = []
for _ in range(q):
    params = read_line().split()
    command = params[0]
    if ADD_RIGHT == command:
        count = int(params[1])
        name = params[2]

        counts[name] += count
        train.append((count, name))

    if DELETE_RIGHT == command:
        count = int(params[1])
        while len(train) and count > 0:
            last_count, last_name = train.pop()
            removed = min(count, last_count)

            count -= removed
            counts[last_name] -= removed

            last_count -= removed
            if last_count > 0:
                train.append((last_count, last_name))

    if GET_COUNT == command:
        name = params[1]

        answer = counts[name]
        answers.append(answer)

print('\n'.join(map(str, answers)))
