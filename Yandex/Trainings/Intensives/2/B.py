def read_ints():
    return map(int, input().split())


n, k = read_ints()
a = list(read_ints())


def get_ans():
    window = set()
    for i, v in enumerate(a):
        if v in window:
            return True

        window.add(v)
        if i >= k:
            window.remove(a[i - k])

    return False


print("YES" if get_ans() else "NO")
