import math


file_name = 'spiral'

with open(file_name + '.in', 'r') as f_in:
    def read_line():
        return f_in.readline().strip()


    def read_int():
        return int(read_line())


    def read_ints():
        return map(int, read_line().split())

    omega, velocity, start_distance, total_time = read_ints()


def get_ans():
    ITERATIONS = 100

    def get_point(time):
        angle = (omega * time) / 180.0 * math.pi
        end_distance = start_distance + velocity * time
        x = end_distance * math.cos(angle)
        y = end_distance * math.sin(angle)
        return x, y

    def min_x_time(left_time, right_time):
        for _ in range(ITERATIONS):
            m1 = left_time + (right_time - left_time) / 3.0
            m2 = right_time - (right_time - left_time) / 3.0
            x1, _ = get_point(m1)
            x2, _ = get_point(m2)
            if x1 < x2:
                right_time = m2
            else:
                left_time = m1
        return left_time

    def max_x_time(left_time, right_time):
        for _ in range(ITERATIONS):
            m1 = left_time + (right_time - left_time) / 3.0
            m2 = right_time - (right_time - left_time) / 3.0
            x1, _ = get_point(m1)
            x2, _ = get_point(m2)
            if x1 > x2:
                right_time = m2
            else:
                left_time = m1
        return left_time

    def min_y_time(left_time, right_time):
        for _ in range(ITERATIONS):
            m1 = left_time + (right_time - left_time) / 3.0
            m2 = right_time - (right_time - left_time) / 3.0
            _, y1 = get_point(m1)
            _, y2 = get_point(m2)
            if y1 < y2:
                right_time = m2
            else:
                left_time = m1
        return left_time

    def max_y_time(left_time, right_time):
        for _ in range(ITERATIONS):
            m1 = left_time + (right_time - left_time) / 3.0
            m2 = right_time - (right_time - left_time) / 3.0
            _, y1 = get_point(m1)
            _, y2 = get_point(m2)
            if y1 > y2:
                right_time = m2
            else:
                left_time = m1
        return left_time

    end_angle_grad = omega * total_time

    min_x = float(start_distance)
    max_x = float(start_distance)
    min_y = 0.0
    max_y = 0.0

    for grad in (0, 90, 180, 270):
        if end_angle_grad >= grad:
            angle_grad = ((end_angle_grad - grad) // 360) * 360 + grad
            angle_time = angle_grad / omega

            next_time = min(total_time, angle_time + 90.0 / omega)

            times = [
                min_x_time(angle_time, next_time),
                max_x_time(angle_time, next_time),
                min_y_time(angle_time, next_time),
                max_y_time(angle_time, next_time),
                angle_time,
            ]

            for check_time in times:
                x, y = get_point(check_time)
                min_x = min(min_x, x)
                max_x = max(max_x, x)
                min_y = min(min_y, y)
                max_y = max(max_y, y)

    return min_x, min_y, max_x, max_y

min_x, min_y, max_x, max_y = get_ans()

with open(file_name + '.out', 'w') as f_out:
    f_out.write(f'{min_x:.10f} {min_y:.10f}\n')
    f_out.write(f'{max_x:.10f} {max_y:.10f}\n')
