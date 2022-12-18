def read_int():
    return int(input())
    

n = read_int()
a = [read_int() for _ in range(n)]

ans = [-1]
for i, dist in enumerate(a, 1):
    prev_ans = ans[-1]
    cur_ans = max(prev_ans + 1, dist - i)
    ans.append(cur_ans)

print(*ans[1:], sep='\n')
