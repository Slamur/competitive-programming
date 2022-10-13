s = input()

b = 0
for c in s[::-1]:
    if c == '0':
        b += 1
    else:
        break

print(b)
