def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve():
    n = read_int()
    a = list(read_ints())

    def get_ans():
        prefs = [0] * (n + 1)
        for i in range(n):
            prefs[i + 1] = prefs[i] + a[i]

        total = prefs[-1]

        def ceil(numerator, denominator):
            result = numerator // denominator
            if result * denominator < numerator:
                result += 1

            return result

        ans_percents = {0}
        for percent in range(101):
            total_left = total * percent
            total_right = total_left + total

            # 100 * (pref + x) in [tnl; tnr)

            for file_index in range(n):
                file_left = 100 * prefs[file_index]

                file_x_left = ceil(total_left - file_left, 100)
                file_x_left = max(file_x_left, 1)

                file_size = a[file_index]

                file_x_right = ceil(total_right - file_left, 100)
                file_x_right = min(file_x_right, file_size + 1)

                # file x in [fxl, fxr)

                x_left = ceil(file_size * percent, 100)
                x_right = ceil(file_size * (percent + 1), 100)

                # x in [x_left, x_right)

                if max(file_x_left, x_left) < min(file_x_right, x_right):
                    ans_percents.add(percent)
                    break

        return ans_percents

    ans = sorted(list(get_ans()))
    print(*ans, sep='\n')


if __name__ == '__main__':
    solve()
