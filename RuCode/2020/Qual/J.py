class vect:

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def len2(self):
        return self.x * self.x + self.y * self.y

    def minus(self, other):
        return vect(self.x - other.x, self.y - other.y)

    def cos(self, other):
        return self.x * other.x + self.y * other.y

    def sin(self, other):
        return self.x * other.y - self.y * other.x


def square(a, b):
    return abs(a.sin(b))


def getAnswer(n, circles):
    mults = []
    squares = []

    for circle in circles:
        mult = 1
        for j in range(len(circle)):
            next = (j + 1) % len(circle)
            len2 = circle[j].minus(circle[next]).len2()
            mult *= len2

        mults.append(mult)

        sq = square(circle[1].minus(circle[0]), circle[2].minus(circle[0]))
        squares.append(sq * sq)

    used = [False] * n

    ans = 0

    for i in range(n):
        if used[i]:
            continue

        cnt = 0
        for j in range(i, n):
            if mults[i] * squares[j] == mults[j] * squares[i]:
                cnt += 1
                used[j] = True

        ans = max(ans, cnt)

    return ans


n = int(input())
circles = []
for i in range(n):
    coords = list(map(int, input().split()))

    circle = []
    for j in range(0, len(coords), 2):
        x = coords[j]
        y = coords[j + 1]
        circle.append(vect(x, y))

    circles.append(circle)

ans = getAnswer(n, circles)
print(ans)