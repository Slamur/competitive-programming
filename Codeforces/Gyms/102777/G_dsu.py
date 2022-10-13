from typing import List


def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n, e_count = read_ints()
edges = [tuple(read_ints()) for _ in range(e_count)]


class DSU:
    __slots__ = [
        'parents',
        'sizes',
    ]

    parents: List[int]
    sizes: List[int]

    def __init__(self, n):
        self.parents = list(range(n))
        self.sizes = [1] * n

    def _get(self, v):
        if v == self.parents[v]:
            return v

        return self._get(self.parents[v])

    def merge(self, a, b):
        a = self._get(a)
        b = self._get(b)

        if a == b:
            return

        if self.sizes[a] < self.sizes[b]:
            a, b = b, a

        self.parents[b] = a
        self.sizes[a] += self.sizes[b]

    def is_group(self, v):
        return v == self._get(v) and self.sizes[v] > 1


dsu = DSU(n)
for a, b in edges:
    dsu.merge(a, b)

ans = 0
for v in range(n):
    if dsu.is_group(v):
        ans += 1

print(ans)

