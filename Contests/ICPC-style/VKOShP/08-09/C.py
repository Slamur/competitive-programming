file_name = 'codes'

with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    n, k = read_ints()
    words = [read_string() for _ in range(n)]


def get_ans():
    ans = []

    prefixes = dict()
    for word in words:
        if len(word) <= k:
            ans.append(word)
        else:
            prefixes[word[:k + 1]] = word

    ans.extend(prefixes.values())

    return ans


ans = get_ans()
with open(file_name + '.out', 'w') as f_out:
    f_out.write(str(len(ans)) + '\n')
    f_out.write('\n'.join(ans))
