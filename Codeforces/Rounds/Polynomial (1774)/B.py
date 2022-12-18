def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def solve_test():
    n, m, k = read_ints()
    a = list(read_ints())

    def get_answer():
        if m < k:
            return False

        sorted_a = sorted(a, reverse=True)

        small_size = n // k
        large_size = small_size + 1

        large_count = n % k
        small_count = k - large_count

        limits = [large_size] * large_count
        limits.extend([small_size] * small_count)

        for index, count in enumerate(sorted_a[:k]):
            if limits[index] < count:
                return False

        return True

    print('YES' if get_answer() else 'NO')

t = read_int()
for _ in range(t):
    solve_test()
