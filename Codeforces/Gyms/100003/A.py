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
    for passes in range(1, max_passes + 1):
        max_seat_rows = (w - passes * a) // y

        if n > max_seat_rows * max_seat_in_row:
            continue

        max_rows_near_passes = min(max_seat_rows, 2 * passes)
        max_seats_near_passes = min(n, max_rows_near_passes * max_seat_in_row)

        ans = max(ans, max_seats_near_passes)

    return ans


ans = get_ans()
with open(file_name + '.out', 'w') as f_out:
    f_out.write(str(ans) + '\n')
