#include <bits/stdc++.h>

void init_io() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
}

using ll = int64_t;
using vi = std::vector<int>;

using edge_t = std::pair<int, int>;
using edge_graph_t = std::vector<std::vector<edge_t>>;
using graph_t = std::vector<vi>;

void solve() {
	int n;
	std::cin >> n;
	
	edge_graph_t graph(n);
	for (int e = 0; e < n - 1; ++e) {
		int from, to, color;
		std::cin >> from >> to >> color;
		--from, --to, --color;
		
		graph[from].emplace_back(to, color);
		graph[to].emplace_back(from, color);
	}
	
	auto get_answer = [&]() {
		int size = n + n;
		
		graph_t color_graph(size);
		std::vector<vi> color_stacks(size);
		
		vi tree_sizes(n, 0);
		
		vi tin(size, size), tout(size, size);
		int timer = 0;
		
		std::function<void(int, int, int)> dfs = [&](int from, int parent, int from_color) {
			tin[from] = timer++;
			
			if (from_color != -1) {
				auto& color_stack = color_stacks[from_color];
				while (tout[color_stack.back()] < tin[from]) {
					color_stack.pop_back();
				}
				color_graph[color_stack.back()].push_back(from);
				color_stack.push_back(from);
			}
			
			tree_sizes[from] = 1;
			
			for (auto& [to, to_color] : graph[from]) {
				if (to == parent) continue;
				
				dfs(to, from, to_color);
				tree_sizes[from] += tree_sizes[to];
			}
			
			tout[from] = timer++;
		};
		
		vi color_roots(n);
		for (int color = 0; color < n; ++color) {
			int color_root = color_roots[color] = color + n;
			
			color_stacks[color].push_back(color_root);
			tin[color_root] = 0;
			tout[color_root] = size;
		}
		
		int root = 0;
		dfs(root, -1, -1);
		
		vi color_sizes(size, 0);
		for (int v = 0; v < n; ++v) {
			color_sizes[v] = tree_sizes[v];
		}
		
		for (int color = 0; color < n; ++color) {
			color_sizes[color_roots[color]] = n;
		}
		
		for (int v = 0; v < size; ++v) {
			for (int to : color_graph[v]) {
				color_sizes[v] -= tree_sizes[to];
			}
		}
		
		ll answer = 0;
		
		for (int v = 0; v < size; ++v) {
			for (int to : color_graph[v]) {
				answer += (ll)color_sizes[v] * color_sizes[to];
			}
		}
		
		return answer;
	};
	
	ll answer = get_answer();
	std::cout << answer << "\n";
}

int main() {
    init_io();
    solve();
    return 0;
}
