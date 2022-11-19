def read_ints():
    return map(int, input().split())


def read_int():
    return int(input())


n = read_int()
removed = list(str(digit) for digit in read_ints())

ans = 0

password_length = 6
for i in range(10**password_length):
    password = str(i)
    while len(password) < 6:
        password = '0' + password

    can = True
    for digit in password:
        if digit in removed:
            can = False

    if len(set(password)) != 2:
        can = False

    password = ''.join(sorted(password))

    left_half = int(password[:password_length // 2])
    right_half = int(password[password_length // 2:])

    if left_half % 111 != 0 or right_half % 111 != 0:
        can = False

    if can:
        ans += 1

print(ans)