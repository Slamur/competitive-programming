def read_ints():
    return map(int, input().split())


n, a, b, d = read_ints()

b = min(b, a * d)

left_start = n - n % d
left_ans = (left_start // d) * b + (n - left_start) * a

right_start = left_start + d
right_ans = (right_start // d) * b + (right_start - n) * a

ans = min(left_ans, right_ans)
print(ans)
