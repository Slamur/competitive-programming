file_name = 'sum'

with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    a_str, b_str, c_str = [read_string() for _ in range(3)]


def get_ans():
    def separate(x):
        x = str(x)

        last_zero = len(x)
        while last_zero - 1 > 0 and x[last_zero - 1] == '0':
            last_zero -= 1

        return int(x[:last_zero]), len(x) - last_zero

    a, az = separate(a_str)
    b, bz = separate(b_str)
    c, cz = separate(c_str)

    max_zeros = max(az, bz, cz)

    ans = [max_zeros - az, max_zeros - bz, max_zeros - cz]
    no_ans = []

    # a + b = c * 10^k
    ab, abz = separate(a + b)
    if ab == c:
        ans[2] += abz
        return ans

    # a + b * 10^k = c
    if c >= a:
        ca, caz = separate(c - a)
        if ca == b:
            ans[1] += caz
            return ans

    # a * 10^k + b = c
    if b >= a:
        cb, cbz = separate(c - b)
        if cb == a:
            ans[0] += cbz
            return ans

    return no_ans


ans = get_ans()

with open(file_name + '.out', 'w') as f_out:
    if len(ans) == 0:
        f_out.write('NO' + '\n')
    else:
        f_out.write('YES' + '\n')
        ans_str = map(str, ans)
        f_out.write(' '.join(ans_str) + '\n')
