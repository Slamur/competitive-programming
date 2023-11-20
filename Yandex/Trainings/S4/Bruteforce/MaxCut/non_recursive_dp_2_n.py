def solve():
	n = int(input())
	
	graph = [list(map(int, input().split())) for _ in range(n)]
	
	def get_bit(mask, bit):
		return (mask >> bit) & 1
		
	subsets = (1 << n)
	cuts = [0] * subsets
	
	v0s = [0] * subsets
	
	indexes = dict(
		(1 << v, v)
		for v in range(n)
	)
	
	for v in range(n):
		v_graph = graph[v]
		total_sum = sum(v_graph[:v])
				
		pref_subsets = (1 << v)		
		v0s[0] = 0
		
		for subset in range(1, pref_subsets):	
			prev_subset = subset & (subset - 1)
			smallest_bit = subset ^ prev_subset
			
			smallest_u = indexes[smallest_bit]
			v0s[subset] = v0s[prev_subset] + v_graph[smallest_u]

		for subset in range(pref_subsets - 1, -1, -1):
			cut = cuts[subset]
			
			v_0 = v0s[subset]
			v_1 = total_sum - v_0
			
			cuts[subset] = max(cuts[subset], cut + v_0)
			
			v_subset = subset | (1 << v)
			cuts[v_subset] = max(cuts[v_subset], cut + v_1)
		
	ans_cut, ans_subset = max(
		zip(cuts, range(subsets))
	)		

	ans_parts = [get_bit(ans_subset, bit) for bit in range(n)]
	
	print(ans_cut)
	print(*[part + 1 for part in ans_parts])

if __name__ == '__main__':
	solve()
