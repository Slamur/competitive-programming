def read_ints():
    return map(int, input().split())
    

def read_int():
    return int(input())
    
    
x_size, y_size = read_ints()
a = [input() for _ in range(x_size)]


cube, line, z_bot, z_top, trident = range(5)
shifts = [
    [(0, 1), (1, 0), (1, 1)], # cube
    [(0, 1), (0, 2), (0, 3)], # line
    [(0, 1), (-1, 1), (-1, 2)], # z_bot
    [(0, 1), (1, 1), (1, 2)], # z_top
]

other = len(shifts)

def get_type(x, y):
    if a[x][y] == '.':
        return -1
    
    for i, fs in enumerate(shifts):
        cnt = 0
        for xs, ys in fs:
            if 0 <= x + xs < x_size and 0 <= y + ys < y_size:
                if a[x][y] == a[x + xs][y + ys]:
                    cnt += 1
                    
        if cnt == 3:
            return i
            
    return other
    

counts = [0] * (other + 2)
for it in range(2):
    for x in range(x_size):
        for y in range(y_size):
            t = get_type(x, y)
            counts[t + 1] += 1
            
    a_transposed = [[a[x][y] for x in range(x_size)] for y in range(y_size)]
    
    a = a_transposed
    x_size, y_size = y_size, x_size
    
    shifts[z_bot], shifts[z_top] = shifts[z_top], shifts[z_bot]
    
counts = counts[1:]
counts[cube] //= 2 # calculated twice

counts[other] -= 6 * counts[cube]
for t in [line, z_bot, z_top]:
    counts[other] -= 7 * counts[t]

counts[other] //= 2 # calculated twice
counts[other] //= 4 # 4 letters -> 1 figure

print(*counts, sep='\n')
