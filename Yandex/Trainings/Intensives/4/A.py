def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


groups_count = read_int()
group_sizes = list(read_ints())

rooms_count = read_int()
room_sizes = list(read_ints())

group_sizes.sort()
room_sizes.sort()

ans = 0

room_index = 0
for group_size in group_sizes:
    while room_index < rooms_count and room_sizes[room_index] < group_size:
        room_index += 1

    if room_index < rooms_count:
        ans += 1
        room_index += 1

print(ans)
