file_name = 'numbers'

with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    n, k = read_ints()


def get_ans():
    inf = 9 * 10**18
    max_size = 0
    while k ** max_size <= inf // k:
        max_size += 1

    goods = [[0] * k for _ in range(max_size)]
    for size in range(1, max_size):
        for first in range(k):
            goods[size][first] += sum(goods[size - 1])

            if size % 2 == 0 and first != 0:
                goods[size][first] += 1  # f000

    ans = [0]

    need = n - 1
    for size in range(max_size - 1, -1, -1):
        if ans[-1] != 0 and size % 2 == 1:
            if need == 0:
                # found ans (f000)
                ans.extend([0] * size)
                return ans
            else:
                need -= 1

        for first in range(k):
            if goods[size][first] <= need:
                need -= goods[size][first]
                continue

            ans.append(first)
            break

    return [-1]


ans = get_ans()

decimal_ans = 0
for digit in ans:
    decimal_ans *= k
    decimal_ans += digit

with open(file_name + '.out', 'w') as f_out:
    f_out.write(str(decimal_ans) + '\n')
