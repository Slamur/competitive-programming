from collections import Counter


s = input()
t = input()

is_anagram = Counter(s) == Counter(t)
print('YES' if is_anagram else 'NO')
