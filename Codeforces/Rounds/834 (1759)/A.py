def read_int():
    return int(input())
    
    
def read_ints():
    return map(int, input().split())
    

universum = 'Yes' * 100
    

def solve_test():
    s = input()
    
    def get_ans():
        return s in universum
        
    print('YES' if get_ans() else 'NO')


t = read_int()
for _ in range(t):
    solve_test()
