def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


x1, y1, x2, y2, x3, y3, z3 = read_ints()


def scalar(xa, ya, xb, yb):
    return xa * xb + ya * yb


def vector(xa, ya, xb, yb):
    return xa * yb - xb * ya


def len_2(x, y):
    return x * x + y * y


def line(xa, ya, xb, yb):
    a = (yb - ya)
    b = (xa - xb)
    c = a * xa + b * ya

    return a, b, c


def intersection(line_1, line_2):
    a1, b1, c1 = line_1
    a2, b2, c2 = line_2

    d = a1 * b2 - a2 * b1
    da = c1 * b2 - c2 * b1
    db = a1 * c2 - a2 * c1

    return d, da, db


def inside(xa, ya, xb, yb, xc, yc):
    sc = scalar(xa - xc, ya - yc, xb - xc, yb - yc)
    vc = vector(xa - xc, ya - yc, xb - xc, yb - yc)

    return vc == 0 and sc <= 0


def is_stick(xa, ya, xb, yb, xc, yc, xd, yd):
    sc = scalar(xb - xa, yb - ya, xd - xc, yd - yc)
    vc = vector(xb - xa, yb - ya, xd - xc, yd - yc)

    return (xa, ya) == (xc, yc) and vc == 0 and sc < 0


def get_ans(x1, y1, x2, y2, x3, y3, z3):
    no_ans = 'N'
    many = 'J'
    stick = 'I'
    corner = 'V'
    trio = 'T'
    cross = 'X'

    x0, y0 = 0, 0

    in_0 = inside(x1, y1, x2, y2, x0, y0)

    if z3 != 0:
        # check (0, 0)
        if not in_0:
            return no_ans

        l1 = len_2(x1, y1)
        l2 = len_2(x2, y2)

        started_0 = min(l1, l2) == 0

        if started_0:
            return corner

        return trio
    else:
        line_1 = line(x1, y1, x2, y2)
        line_2 = line(x0, y0, x3, y3)

        d, dx, dy = intersection(line_1, line_2)

        in_1 = inside(x0, y0, x3, y3, x1, y1)
        in_2 = inside(x0, y0, x3, y3, x2, y2)
        in_3 = inside(x1, y1, x2, y2, x3, y3)

        if d == 0:
            if not (in_0 or in_1 or in_2 or in_3):
                return no_ans

            if is_stick(x1, y1, x2, y2, x3, y3, x0, y0) \
                    or is_stick(x1, y1, x2, y2, x0, y0, x3, y3) \
                    or is_stick(x2, y2, x1, y1, x0, y0, x3, y3) \
                    or is_stick(x2, y2, x1, y1, x3, y3, x0, y0):
                return stick

            return many

        # lines intersecting

        x1 *= d
        y1 *= d
        x2 *= d
        y2 *= d
        x0 *= d
        y0 *= d
        x3 *= d
        y3 *= d

        # both segments should contain intersection
        if not (inside(x1, y1, x2, y2, dx, dy)
                and inside(x0, y0, x3, y3, dx, dy)):
            return no_ans
            
        if (in_1 or in_2) and (in_0 or in_3):
            return corner

        if (in_0 or in_1 or in_2 or in_3):
            return trio

        return cross


ans = get_ans(x1, y1, x2, y2, x3, y3, z3)
print(ans)
