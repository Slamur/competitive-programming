def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


t1 = list(read_ints())
t2 = list(read_ints())


def scalar(xa, ya, xb, yb):
    return xa * xb + ya * yb


def vector(xa, ya, xb, yb):
    return xa * yb - xb * ya


def len_2(x, y):
    return x * x + y * y
    

class Triangle:

    def __init__(self, t):
        self.v = []
        for i in range(3):
            self.v.append((t[2 * i], t[2 * i + 1]))

    def vec(self, i, j):
        xs, ys = self.v[i]
        xe, ye = self.v[j]
        return xe - xs, ye - ys

    def len2(self, i, j):
        x, y = self.vec(i, j)
        return len_2(x, y)

    def square(self):
        ax, ay = self.vec(0, 1)
        bx, by = self.vec(0, 2)

        return abs(vector(ax, ay, bx, by))
        
    def get_sides(self):
    	return [self.len2(i, (i + 1) % 3) for i in range(3)]	


def get_ans():
    tr_1 = Triangle(t1)
    tr_2 = Triangle(t2)

    s1 = tr_1.square()
    s2 = tr_2.square()

    if s1 > s2:
        return 1

    if s1 < s2:
        return 2

    sides_1 = tr_1.get_sides()
    sides_2 = tr_2.get_sides()
    
    if sorted(sides_1) == sorted(sides_2):
    	return 0

    return 3


ans = get_ans()
print(ans)
