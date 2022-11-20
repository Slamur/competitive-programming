file_name = 'shelves'

with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    left_size, right_size = read_ints()
    left_heights = list(read_ints())
    right_heights = list(read_ints())


def get_ans():
    left_starts = [0] * (left_size + 1)
    for i in range(left_size):
        left_starts[i + 1] = left_starts[i] + left_heights[i]

    right_starts = [0] * (right_size + 1)
    for j in range(right_size):
        right_starts[j + 1] = right_starts[j] + right_heights[j]

    segments = []
    for i in range(left_size):
        end = left_starts[i] + left_heights[i]
        segments.append((end, left_starts[i], i, 0))

    for j in range(right_size):
        end = right_starts[j] + right_heights[j]
        segments.append((end, right_starts[j], j, 1))

    ans = [[] for _ in range(2)]

    last_end = -1
    segments.sort()
    for end, start, index, side in segments:
        if start >= last_end:
            last_end = end
            ans[side].append(index + 1)

    return ans


left_ans, right_ans = get_ans()
with open(file_name + '.out', 'w') as f_out:
    f_out.write(f'{len(left_ans)} {len(right_ans)}' + '\n')
    f_out.write(' '.join(map(str, left_ans)) + '\n')
    f_out.write(' '.join(map(str, right_ans)) + '\n')
