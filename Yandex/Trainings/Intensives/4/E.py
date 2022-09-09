def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


def read_string():
    return input()


need_name = read_string()
n = read_int()
names = [read_string() for _ in range(n)]


def to_spaced(name):
    spaces = 0
    for c in name:
        if ' ' == c:
            spaces += 1
        else:
            break

    return [spaces, name[spaces:]]


spaced_names = list(map(to_spaced, names))

path = [[-1, ""]]
for spaces, name in spaced_names:
    # [0] - spaces, [1] - name
    while path[-1][0] >= spaces:
        path.pop()

    if path[-1][0] + 1 != spaces:
        raise Exception()

    path.append([spaces, name])
    if name == need_name:
        break

path_names = [name for _, name in path]
print("/".join(path_names))
