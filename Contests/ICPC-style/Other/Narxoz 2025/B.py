read_line = input 


def read_token(parse=str):
    return parse(read_line())


def read_tokens(parse=str):
    return map(parse, read_line().split())


def yes_no(yes, yes_str='YES', no_str='NO'):
    print(yes_str if yes else no_str)
    return yes


def solve():
    x, y, z, A, B, C, theta_inp, phi_inp, v = read_tokens(float)

    def get_ans():
        g = 9.81

        from math import pi, cos, sin, sqrt

        theta, phi = theta_inp * pi / 180, phi_inp * pi / 180

        inf = float('inf')

        def solve_linear(k, b, min_x, max_x):
            # kx + b in [min_x, max_x]

            if k == 0:
                return [-inf, inf] if min_x <= b <= max_x else [-1, -1]
            
            limits = sorted([(min_x - b) / k, (max_x - b) / k])
            return limits
        
        def solve_quadratic(a, b, c, max_x):
            # ax^2 + bx + c in [0, max_x]
            # a < 0

            d0 = b * b - 4 * a * c

            l0 = None
            if d0 < 0:
                # no intersection with 0
                l0 = [-1, -1]
            else:
                x10, x20 = (-b - sqrt(d0)) / (2 * a), (-b + sqrt(d0)) / (2 * a)
                if x10 > x20:
                    x10, x20 = x20, x10

                l0 = [x10, x20]

            dm = b * b - 4 * a * (c - max_x)

            lm = None
            if dm < 0:
                lm = [[-inf, 0], [0, inf]]
            else:
                x1m, x2m = (-b - sqrt(dm)) / (2 * a), (-b + sqrt(dm)) / (2 * a)
                if x1m > x2m:
                    x1m, x2m = x2m, x1m

                lm = [[-inf, x1m], [x2m, inf]]

            return [l0, lm]
        
        x_limits = solve_linear(v * cos(phi) * cos(theta), x, 0, A)
        y_limits = solve_linear(v * cos(phi) * sin(theta), y, 0, B)

        z0_limits, zm_limits = solve_quadratic(-0.5 * g, v * sin(phi), z, C)

        valid_limits = [0, inf]

        def intersect(seg_1, seg_2):
            l1, r1 = seg_1
            l2, r2 = seg_2

            return [max(l1, l2), min(r1, r2)]
        
        ans = intersect(valid_limits, x_limits)
        ans = intersect(ans, intersect(valid_limits, y_limits))

        ans = intersect(ans, intersect(valid_limits, z0_limits))
        for zm_limit in zm_limits:
            candidate = intersect(ans, intersect(valid_limits, zm_limit))

            if candidate[0] <= candidate[1]:
                return True

        return False

    
    ans = get_ans()
    yes_no(ans)


if __name__ == '__main__':
    solve()
