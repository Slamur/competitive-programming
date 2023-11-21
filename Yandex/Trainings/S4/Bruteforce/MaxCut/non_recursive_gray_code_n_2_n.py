def solve():
	n = int(input())
	
	graph = [list(map(int, input().split())) for _ in range(n)]
	
	def get_bit(mask, bit):
		return (mask >> bit) & 1
		
	indexes = dict(
		(1 << v, v)
		for v in range(n)
	)
	
	subsets = (1 << n) >> 1
	
	cut = 0
	prev_subset = 0
	
	ans_cut, ans_subset = cut, prev_subset
			
	for i in range(1, subsets):
		subset = i ^ (i >> 1)
		
		diff_bit = subset ^ prev_subset
		diff_v = indexes[diff_bit]
		
		prev_subset = subset
		
		v_graph = graph[diff_v]
		v_part = get_bit(subset, diff_v)
		
		for u, edge in enumerate(v_graph):
			cut += -edge if get_bit(subset, u) else edge
		
		if ans_cut < cut:
			ans_cut, ans_subset = cut, subset

	ans_parts = [get_bit(ans_subset, bit) for bit in range(n)]
	
	print(ans_cut)
	print(*[part + 1 for part in ans_parts])

if __name__ == '__main__':
	solve()
