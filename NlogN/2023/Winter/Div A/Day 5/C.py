def read_ints():
    return map(int, input().split())
    

def read_int():
    return int(input())
    
    
n, day, transport = read_ints()
classes = [tuple(read_ints()) for _ in range(n)]

offline, online = 0, 1

classes.append((day, day, online))
n += 1

classes.sort()

home, outside = 1, 0

neg_inf = -(day + day + 1)
dp = [[neg_inf] * (n + 1) for _ in [home, outside]]

dp[home][0] = 0
last_end = 0


for i in range(n):
    cur_start, cur_end, class_type = classes[i]
    
    free_time = cur_start - last_end
    
    ## outside - outside
    rest_between_outside = max(0, free_time - 2 * transport)
    dp[outside][i + 1] = max(dp[outside][i + 1], dp[outside][i] + rest_between_outside)
    
    ## home - outside
    rest_before_transport = free_time - transport
    if rest_before_transport >= 0:
        dp[outside][i + 1] = max(dp[outside][i + 1], dp[home][i] + rest_before_transport)
        
    if class_type == online:
        class_duration = cur_end - cur_start
        
        ## home - home
        dp[home][i + 1] = max(dp[home][i + 1], dp[home][i] + free_time + class_duration)
        
        ## outside - home
        rest_after_transport = free_time - transport
        if rest_after_transport >= 0:
            dp[home][i + 1] = max(dp[home][i + 1], dp[outside][i] + rest_after_transport + class_duration)
    
    last_end = cur_end

print(dp[home][-1])
