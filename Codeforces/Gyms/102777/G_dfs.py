from typing import List


def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n, e_count = read_ints()
edges = [tuple(read_ints()) for _ in range(e_count)]

graph = [[] for _ in range(n)]
for a, b in edges:
	graph[a].append(b)
	graph[b].append(a)
	

def dfs(v, used):
	if used[v]:
		return 0
	
	used[v] = True
	
	cnt = 1
	for v_to in graph[v]:
		cnt += dfs(v_to, used)
	return cnt

ans = 0

used = [False] * n
for v in range(n):
	if dfs(v, used) > 1:
		ans += 1

print(ans)

