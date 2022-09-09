n = int(input())

next_height = 1

# O(sqrt(n)) complexity
while next_height <= n:
    n -= next_height
    next_height += 1

print(next_height - 1)
