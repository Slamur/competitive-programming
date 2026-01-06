from collections import defaultdict

file_name = 'gems'

with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    n, k = read_ints()
    text = read_string()

    goods = [read_string() for _ in range(k)]


def get_ans():
    ans = 0

    starts = defaultdict(list)
    for start, end in goods:
        starts[end].append(start)

    counts = defaultdict(int)
    for letter in text:
        for start in starts[letter]:
            ans += counts[start]
        counts[letter] += 1

    return ans


ans = get_ans()
with open(file_name + '.out', 'w') as f_out:
    f_out.write(str(ans) + '\n')
