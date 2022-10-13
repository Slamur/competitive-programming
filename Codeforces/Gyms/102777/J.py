def read_int():
    return int(input())


def read_strings():
    return input().split()


def read_ints():
    return map(int, read_strings())


n, m, k = read_ints()

def get_answer(n, m, k):
    k += 1

    if n > m:
        n, m = m, n

    lw = 0
    rw = (n - 1) // 2 + 1

    while rw - lw > 1:
        mw = (lw + rw) // 2

        cnt = 2 * mw * (n + m - 2 * mw)
        if cnt < k:
            lw = mw
        else:
            rw = mw

    k -= 2 * lw * (n + m - 2 * lw)

    lx, ly = rw, rw
    rx, ry = n - lx + 1, m - ly + 1

    cx, cy = lx, ly - 1

    delta = min(ry - cy, k)
    cy += delta
    k -= delta

    delta = min(rx - cx, k)
    cx += delta
    k -= delta

    delta = min(cy - ly, k)
    cy -= delta
    k -= delta

    delta = min(cx - lx, k)
    cx -= delta
    k -= delta

    d = cx + cy - 2
    color = d % 7
    return color + 1


ans = get_answer(n, m, k)
print(ans)

