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

root = 0
degrees = [len(graph[v]) for v in range(n)]
degrees[root] += 1 # fictive super root

leaves = deque(
    filter(lambda v: degrees[v] == 1, range(n))
)

sizes = [0] * n

used = [False] * n
while len(leaves) > 0:
    v_from = leaves.popleft()
    sizes[v_from] = 1
    used[v_from] = True

    for v_to in graph[v_from]:
        if used[v_to]:
            sizes[v_from] += sizes[v_to]
        else:
            degrees[v_to] -= 1
            if degrees[v_to] == 1:
                leaves.append(v_to)

print(" ".join(map(str, sizes)))
