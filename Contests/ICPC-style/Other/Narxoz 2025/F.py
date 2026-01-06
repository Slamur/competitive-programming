read_line = input 


def read_token(parse=str):
    return parse(read_line())


def read_tokens(parse=str):
    return map(parse, read_line().split())


def yes_no(yes, yes_str='YES', no_str='NO'):
    print(yes_str if yes else no_str)
    return yes


def solve():
    n = read_token(int)
    a = list(read_tokens(int))
    b = list(read_tokens(int))

    def get_ans():
        no_ans = -1

        from collections import defaultdict

        a_lines = defaultdict(list)
        for i, va in enumerate(a):
            a_lines[va - i].append(i)

        b_lines = defaultdict(list)
        for j, vb in enumerate(b):
            b_lines[vb - j].append(j)

        for bd, blist in b_lines.items():
            if bd not in a_lines:
                return no_ans
            
            if len(blist) != len(a_lines[bd]):
                return no_ans
            
        mapping = [-1] * n
        for bd, b_pos in b_lines.items():
            a_pos = a_lines[bd]

            for ap, bp in zip(a_pos, b_pos):
                mapping[ap] = bp

        inf = n + 1

        def merge(arr, left, mid, right):
            ql = arr[left:mid]
            qr = arr[mid:right]

            ql.append(inf)
            qr.append(inf)

            res = 0

            il, ir = 0, 0
            for k in range(left, right):
                if ql[il] <= qr[ir]:
                    arr[k] = ql[il]
                    res += ir
                    il += 1
                else:
                    arr[k] = qr[ir]
                    ir += 1

            return res

        def inv_count(arr, left=0, right=n):
            size = (right - left)
            if size <= 1:
                return 0
            
            mid = (left + right) // 2
            
            ans_l = inv_count(arr, left, mid)
            ans_r = inv_count(arr, mid, right)
            return ans_l + ans_r + merge(arr, left, mid, right)

        return inv_count(mapping)

    ans = get_ans()
    print(ans)


if __name__ == '__main__':
    solve()
