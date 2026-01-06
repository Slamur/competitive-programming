file_name = 'dfs'

with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    n, k = read_ints()
    order = [read_int() for _ in range(k)]


def get_ans():
    ans = []

    first = [-1] * (n + 1)
    last = [-1] * (n + 1)
    for i, v in enumerate(order):
        if first[v] == -1:
            first[v] = i

        last[v] = i

    stack = []
    cur_children = [-1] * (n + 1)

    root = 0
    stack.append(root)
    for i, v in enumerate(order):
        if i == first[v]:
            for p in stack:
                if p == root:
                    continue

                if cur_children[p] <= v:
                    ans.append((p, v))

            parent = stack[-1]
            cur_children[parent] = v

            stack.append(v)

        if i == last[v]:
            stack.pop(-1)

    return ans


ans = get_ans()
with open(file_name + '.out', 'w') as f_out:
    f_out.write(str(len(ans)) + '\n')

    edges = [f'{a} {b}' for a, b in ans]
    f_out.write('\n'.join(edges))
