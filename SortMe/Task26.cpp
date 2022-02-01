//#pragma GCC optimize("conserve-stack")

#include <bits/stdc++.h>
#include <sys/resource.h>

void init_stack_size() {
	const rlim_t kStackSize = 256 * 1024 * 1024;   // min stack size = 16 MB
	
    struct rlimit rl;
    int result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }
}

class DSU {
	
	std::vector<int> parents;
	std::vector<int> sizes;
	
public:
	DSU(int size)
	: parents(size)
	, sizes(size, 1) {
		for (int v = 0; v < size; ++v) parents[v] = v;
	}
	
	void merge(int a, int b) {
		a = get(a);
		b = get(b);
		
		if (a == b) return;
		
		if (sizes[a] < sizes[b]) std::swap(a, b);
		sizes[a] += sizes[b];
		parents[b] = a;
	}
	
	int get(int v) {
		int p = parents[v];
		return (v == p ? v : parents[v] = get(p));
	}
	
	int size(int v) {
		return sizes[get(v)];
	}
};

using ll = int64_t;

namespace dfs {
	
	int k;
	ll ans;
	std::vector<std::vector<int>> graph;
	std::vector<ll> sizes;
	
	std::pair<ll, std::list<ll>> dfs(int v, int p) {
		ll self_size = sizes[v];
		
		std::list<ll> counts;
		ll sum = 0;
		
		sum += self_size;
		counts.push_back(self_size); // itself on depth 0
		
		ans += (self_size - 1) * self_size;
		
		int size = counts.size();
		
		for (int ch : graph[v]) {
			if (p == ch) continue;
			
			auto [child_sum, child_counts] = dfs(ch, v);
			child_counts.push_back(0);
			
			while ((int)child_counts.size() > k + 1) {
				child_sum -= child_counts.front();
				child_counts.pop_front();
			}
			
			int child_size = child_counts.size();
			
			if (child_size > size) {
				std::swap(child_counts, counts);
				std::swap(child_sum, sum);
				std::swap(child_size, size);
			}
			
			std::vector<ll> child_prefix(child_counts.rbegin(), child_counts.rend());
			
			{
				for (int child_depth = 1; child_depth < child_size; ++child_depth) {
					child_prefix[child_depth] += child_prefix[child_depth - 1];
				}
			}
			
			{
				auto it = counts.begin();
				ll small_sum = sum;
				
				for (int depth = size - 1; depth >= 0; --depth, ++it) {
					int max_child_depth = k - depth;
					if (max_child_depth >= child_size) break;
					
					ll count = *it;
					ans += 2 * count * child_prefix[max_child_depth]; 
					
					small_sum -= count;					
				}
				
				ans += 2 * small_sum * child_prefix.back();
			}
			
			{
				auto it = counts.rbegin(), child_it = child_counts.rbegin();
				for (int child_depth = 0; child_depth < child_size; ++child_depth, ++it, ++child_it) {
					*it += *child_it;
				}
				sum += child_sum;
			}
		}
		
		return make_pair(sum, move(counts));
	}
};

int main() {
	init_stack_size();
	
	int n, k;
	std::cin >> n >> k;
	
	std::vector<std::vector<std::pair<int, int>>> orig_graph(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v, w;
		std::cin >> u >> v >> w;
		--u, --v;
		orig_graph[u].emplace_back(v, w);
		orig_graph[v].emplace_back(u, w);
	}
	
	DSU dsu(n);
	for (int v = 0; v < n; ++v) {
		for (auto& [u, w] : orig_graph[v]) {
			if (0 == w) dsu.merge(v, u);
		}
	}
	
	dfs::graph.resize(n);
	
	for (int v = 0; v < n; ++v) {
		int v_root = dsu.get(v);
		for (auto& [u, w] : orig_graph[v]) {
			if (1 == w) {
				int u_root = dsu.get(u);
				dfs::graph[v_root].push_back(u_root);
			}
		}
	}
	
	dfs::sizes.resize(n);
	for (int v = 0; v < n; ++v) {
		dfs::sizes[v] = dsu.size(v);
	}
	
	dfs::k = k;
	dfs::ans = 0;
	
	int root = dsu.get(0);
	dfs::dfs(root, -1);
	
	std::cout << dfs::ans << std::endl;
	
	
	return 0;
}

