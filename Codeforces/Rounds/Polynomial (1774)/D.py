def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n, m = read_ints()
    a = [list(read_ints()) for _ in range(n)]

    def get_ans():
        counts = list(map(sum, a))

        total = sum(counts)
        if total % n != 0:
            return None

        need = total // n

        steps = []

        for column in range(m):
            heavy = []
            light = []

            for row in range(n):
                if counts[row] > need and a[row][column] == 1:
                    heavy.append(row)
                if counts[row] < need and a[row][column] == 0:
                    light.append(row)

            size = min(len(heavy), len(light))
            for i in range(size):
                steps.append(
                    ' '.join(map(str, (heavy[i] + 1, light[i] + 1, column + 1)))
                )
                counts[heavy[i]] -= 1
                counts[light[i]] += 1

        if not all(map(lambda count: count == need, counts)):
            return None

        return steps

    ans = get_ans()
    if ans is None:
        return "-1"

    ans_str = [str(len(ans))]
    ans_str.extend(ans)

    return '\n'.join(ans_str)


t = read_int()

answers = []
for _ in range(t):
    answers.append(solve_test())

print("\n".join(answers))
