def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def yes_no(value, yes = "YES", no = "NO"):
    print(yes if value else no)
    return value


def lower_bound(array, value):
    left = -1
    right = len(array)
    while right - left > 1:
        mid = (left + right) // 2
        if array[mid] >= value:
            right = mid
        else:
            left = mid
    return right


def upper_bound(array, value):
    return lower_bound(array, value + 1)


def clamp(value, left, right):
    if value < left:
        return left

    if value > right:
        return right

    return value