#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;
using graph_t = vector<vi>;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, d;
	cin >> n >> d;
	
	graph_t g(n);
	for (int e = 0; e < n - 1; ++e) {
		int from, to;
		cin >> from >> to;
		--from, --to;
		
		g[from].push_back(to);
		g[to].push_back(from);
	}
	
	auto read_need = [&]() {
		int size; 
		cin >> size;
		
		vi need(size);
		for (auto& v : need) {
			cin >> v;
			--v;
		}
		return need;
	};
	
	vi first = read_need();
	vi second = read_need();
	
	auto get_ans = [&]() {
		vi heights(n, 0);
		vi tin(n, -1), tout(n, -1);
		vi parents(n, -1);
		
		int timer = 0;
		function<void(int, int)> dfs_calc = [&](int v, int p) {
			parents[v] = p;
			tin[v] = timer++;
			
			for (int to : g[v]) {
				if (to != p) {
					heights[to] = heights[v] + 1;
					dfs_calc(to, v);
				}
			}
			
			tout[v] = timer++;
		};
		
		int root = 0;
		dfs_calc(root, -1);
		
		vector<vi> need(2, vi(n, false));
		vector<vi> pl_needs = { first, second };
		for (int i = 0; i < 2; ++i) {
			auto& pl_need = pl_needs[i];
			for (int v : pl_need) need[i][v] = true;
		}
				
		ll ans = 0;
		
		vi path;
		
		vi last(2, root);
		
		auto inside = [&](int v, int child) {
			return tin[v] <= tin[child] && tout[child] <= tout[v];
		};
		
		function<void(int)> dfs_ans = [&](int v) {
			path.push_back(v);
			
			for (int i = 0; i < 2; ++i) {
				if (!need[i][v]) {
					continue;
				}
				
				int other = (0 + 1) - i;
				while (!inside(last[other], v)) {
					last[other] = parents[last[other]];
					++ans;
				}
				
				int dist = heights[v] - heights[last[other]];
				if (dist > d) {
					int delta = dist - d;
					ans += delta;
					last[other] = path[heights[v] - d];
				}
				
				while (!inside(last[i], v)) {
					last[i] = parents[last[i]];
					++ans;
				}
				
				ans += heights[v] - heights[last[i]];
				last[i] = v;
			}
			
			for (int to : g[v]) {
				if (to != parents[v]) dfs_ans(to);
			}
			
			path.pop_back();
		};
		
		dfs_ans(root);
		
		for (int i = 0; i < 2; ++i) {
			ans += heights[last[i]];
		}
		
		return ans;
	};
	
	ll ans = get_ans();
	cout << ans << "\n";

	return 0;
}
