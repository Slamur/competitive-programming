file_name = 'aisle'

with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    n, l, w, x, y, a = read_ints()


def get_ans():
    ans = -1

    max_seat_in_row = l // x

    max_passes = w // a
    for k in range(1, max_passes + 1):
        max_seat_rows = (w - k * a) // y

        if n > max_seat_rows * max_seat_in_row:
            continue

        res = 0
        free_seats = n
        free_rows = max_seat_rows

        # between two passes
        inner_segments = k - 1
        max_inner_seat_rows = min(free_rows, 2 * inner_segments)
        free_rows -= max_inner_seat_rows

        inner_seats = min(free_seats, max_inner_seat_rows * max_seat_in_row)
        free_seats -= inner_seats

        res += inner_seats

        # before first and after last
        outer_segments = 2
        max_outer_seat_rows = min(free_rows, outer_segments)
        free_rows -= max_outer_seat_rows

        outer_seats = min(free_seats, max_outer_seat_rows * max_seat_in_row)
        free_seats -= outer_seats

        res += outer_seats

        ans = max(ans, res)

    return ans


ans = get_ans()
with open(file_name + '.out', 'w') as f_out:
    f_out.write(str(ans) + '\n')
