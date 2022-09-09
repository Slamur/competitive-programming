s = input()
t = input()

is_anagram = sorted(s) == sorted(t)
print('YES' if is_anagram else 'NO')
