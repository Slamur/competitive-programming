def read_ints():
    return map(int, input().split())
    

def read_int():
    return int(input())
    
    

n = read_int()
a = list(read_ints())


colors = [-1]
for color in a:
    if colors[-1] != color:
        colors.append(color)
        

max_c = max(colors)
merges = [0] * (max_c + 1)

from collections import Counter
counts = Counter(colors)

for i, color in enumerate(colors[1:-1], 1):
    if colors[i - 1] == colors[i + 1]:
        merges[color] += 1
        
colors.pop(0)

ans, ans_color = -1, -1
for color in colors:
    cur_ans = len(colors) - counts[color] - merges[color]
    if ans < cur_ans:
        ans = cur_ans
        ans_color = color

print(ans, ans_color)
