def solve():
	n = int(input())
	
	graph = [list(map(int, input().split())) for _ in range(n)]
	
	def get_bit(mask, bit):
		return (mask >> bit) & 1
	
	def calc(v, parts_mask, prefix_cut):
		if v == n:
			return (prefix_cut, parts_mask)
		
		ans = None
		for v_part in range(2):
			v_delta = 0
			for u in range(v):
				if get_bit(parts_mask, u) != v_part:
					v_delta += graph[u][v]
			
			parts_mask ^= (v_part << v)
			v_ans = calc(v + 1, parts_mask, prefix_cut + v_delta)
			parts_mask ^= (v_part << v)
			
			if ans is None or ans < v_ans:
				ans = v_ans

		return ans
	
	ans_cut, ans_parts_mask = calc(0, 0, 0)
	ans_parts = [get_bit(ans_parts_mask, bit) for bit in range(n)]
	
	print(ans_cut)
	print(*[part + 1 for part in ans_parts])

if __name__ == '__main__':
	solve()
