n, k = [int(s) for s in input().split()]

facts = [1] * (n + 1)
for i in range(1, n + 1):
	facts[i] = facts[i - 1] * i
	
ans = sum(v**k for v in facts)

while ans % 10 == 0:
	ans //= 10
	
print(ans % 10)