replaces = set(input().split())
max_len = max(map(len, replaces))


def try_shortify(word):
    limit = min(max_len, len(word))
    for prefix_len in range(limit):
        if word[:prefix_len + 1] in replaces:
            return word[:prefix_len + 1]

    return word


text = input().split()

ans = list(map(try_shortify, text))
print(*ans)
