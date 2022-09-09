def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


table_length, socks_count, queries_count = read_ints()
socks = [tuple(read_ints()) for _ in range(socks_count)]
queries = [read_int() for _ in range(queries_count)]

thickness = [0] * (table_length + 2)
for left, right in socks:
    thickness[left] += 1
    thickness[right + 1] -= 1

for x in range(1, len(thickness)):
    thickness[x] += thickness[x - 1]

ans = [thickness[query] for query in queries]
print("\n".join(map(str, ans)))
