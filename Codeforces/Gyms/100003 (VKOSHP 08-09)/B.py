import math

file_name = 'bridge'


class Vector:
    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __mul__(self, other):
        return self.x * other.x + self.y * other.y

    def __mod__(self, other):
        return self.x * other.y - self.y * other.x

    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y)

    def __add__(self, other):
        return Vector(
            x=self.x + other.x,
            y=self.y + other.y,
        )

    def __neg__(self):
        return Vector(
            x=-self.x,
            y=-self.y,
        )

    def __sub__(self, other):
        return self + (-other)

    def orthogonal(self):
        return Vector(
            x=self.y,
            y=-self.x,
        )


class Point(Vector):
    def distance(self, other):
        return (other - self).length()


class Line:
    @classmethod
    def by_points(cls, start: Point, end: Point):
        direction = end - start
        norm = direction.orthogonal()

        return cls(
            norm=norm,
            c=-(norm * start)
        )

    def __init__(self, norm: Vector, c: int):
        self.norm = norm
        self.c = c

    def distance(self, p: Point):
        numerator = self.norm * p + self.c
        denominator = self.norm.length()
        return abs(numerator / denominator)


class Segment:
    def __init__(self, start: Point, end: Point):
        self.start = start
        self.end = end
        self.line = Line.by_points(start, end)

    def distance(self, p: Point):
        sp = p - self.start
        ep = p - self.end

        esp = sp * (self.end - self.start)
        sep = ep * (self.start - self.end)

        if esp >= 0 and sep >= 0:
            return self.line.distance(p)
        else:
            return min(sp.length(), ep.length())


with open(file_name + '.in', 'r') as f_in:
    def read_string():
        return f_in.readline().strip()


    def read_ints():
        return map(int, read_string().split())


    def read_int():
        return int(read_string())


    def read_point():
        x, y = read_ints()
        return Point(
            x=x,
            y=y,
        )


    left_size = read_int()
    left_points = [read_point() for _ in range(left_size)]

    right_size = read_int()
    right_points = [read_point() for _ in range(right_size)]


def get_ans():
    ans = math.inf

    coord_inf = 10**5

    def add_rays(points):
        first_x = points[0].x
        points.insert(0, Point(x=first_x, y=-coord_inf))

        last_x = points[-1].x
        points.append(Point(x=last_x, y=coord_inf))

    add_rays(left_points)
    add_rays(right_points)

    left_segments = [
        Segment(left_points[i - 1], left_points[i])
        for i in range(1, len(left_points))
    ]

    right_segments = [
        Segment(right_points[j - 1], right_points[j])
        for j in range(1, len(right_points))
    ]

    for left_segment in left_segments:
        for right_point in right_points:
            ans = min(ans, left_segment.distance(right_point))

    for right_segment in right_segments:
        for left_point in left_points:
            ans = min(ans, right_segment.distance(left_point))

    return ans


ans = get_ans()
with open(file_name + '.out', 'w') as f_out:
    f_out.write(str(ans) + '\n')
