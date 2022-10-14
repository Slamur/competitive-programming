def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


s = input()


def get_answer():
    good = [
        2, 3, 5, 7, 11, 19, 41, 61, 89, 409, 449, 499, 881, 991, 6469, 6949, 9001, 9049, 9649, 9949, 60649,
        666649, 946669, 60000049, 66000049, 66600049
    ]
    good = sorted(good, reverse=True)

    for p in good:
        ps = str(p)

        removed = []
        pi = 0
        for i in range(len(s)):
            if pi < len(ps) and s[i] == ps[pi]:
                pi += 1
            else:
                removed.append(i)

        if pi == len(ps):
            if len(removed) == 0:
                removed = [-1]

            return p, removed

    raise Exception("IDK")


p, removed = get_answer()
print(p)
print(*removed)

