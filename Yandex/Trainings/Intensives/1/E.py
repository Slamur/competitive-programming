s = input()


def get_ans():
    if len(s) == 1:
        return ""

    letters = list(s)
    n = len(letters)

    all_a = True
    for i in range(n // 2):
        if letters[i] != 'a':
            letters[i] = 'a'
            all_a = False
            break

    if all_a:
        letters[-1] = 'b'

    return "".join(letters)


print(get_ans())
