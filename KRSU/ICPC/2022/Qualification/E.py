from math import log


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


def get_ans(n):
	p = n // 2
	q = 0
	
	if n % 2 == 1 and p >= 2:
		p -= 2
		q += 1
	
	mod = 2022
	ans = pow(2, p, mod) * pow(5, q, mod)
	ans %= mod
	
	return ans


n = read_int()
print(get_ans(n))
