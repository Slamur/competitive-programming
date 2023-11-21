def solve():
	n = int(input())
	
	graph = [list(map(int, input().split())) for _ in range(n)]
	
	def get_bit(mask, bit):
		return (mask >> bit) & 1
		
	subsets = (1 << n)
	cuts = [0]
	
	indexes = dict(
		(1 << v, v)
		for v in range(n)
	)
	
	for v in range(n):
		v_graph = graph[v]
		total_sum = sum(v_graph[:v])
				
		pref_subsets = (1 << v)		
		
		cuts.extend(cuts)
		
		v_0 = 0
		prev_subset = 0
		cuts[1 << v] = total_sum
		
		for i in range(1, pref_subsets):
			subset = i ^ (i >> 1)
			
			diff_bit = subset ^ prev_subset
			diff_u = indexes[diff_bit]
			
			prev_subset = subset
			
			w_delta = v_graph[diff_u]
			v_0 += w_delta if get_bit(subset, diff_u) else -w_delta
			
			cuts[subset] += v_0
			cuts[subset | (1 << v)] += total_sum - v_0
		
	ans_cut, ans_subset = max(
		zip(cuts, range(subsets))
	)		

	ans_parts = [get_bit(ans_subset, bit) for bit in range(n)]
	
	print(ans_cut)
	print(*[part + 1 for part in ans_parts])

if __name__ == '__main__':
	solve()
