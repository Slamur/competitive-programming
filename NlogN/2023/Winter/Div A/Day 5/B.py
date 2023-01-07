def read_ints():
    return map(int, input().split())
    

def read_int():
    return int(input())
    
    
l, r = (list(input()) for _ in range(2))

l = l[::-1]
r = r[::-1]

while len(l) < len(r):
    l.append('0')
    
    
while len(l) > 0 and l[-1] == r[-1]:
    l.pop()
    r.pop()
    
print(len(l))
