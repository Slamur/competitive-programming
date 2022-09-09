from collections import deque


def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n = read_int()
graph = [[] for _ in range(n)]

for _ in range(n - 1):
    v_from, v_to = read_ints()
    v_from -= 1
    v_to -= 1
    graph[v_from].append(v_to)
    graph[v_to].append(v_from)

sizes = [0] * n


def dfs(v_from, p=-1):
    sizes[v_from] = 1
    for v_to in graph[v_from]:
        if v_to == p:
            continue
        sizes[v_from] += dfs(v_to, p=v_from)
    return sizes[v_from]


root = 0
dfs(root)

print(" ".join(map(str, sizes)))
