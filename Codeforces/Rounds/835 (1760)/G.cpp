#include <bits/stdc++.h>

using namespace std;

void solve_test() {
	int n, a, b;
	cin >> n >> a >> b;
	
	using edge = pair<int, int>;
	vector<vector<edge>> g(n + 1);
	
	for (int e = 0; e < n - 1; ++e) {
		int f, t, w;
		cin >> f >> t >> w;
		g[f].emplace_back(t, w);
		g[t].emplace_back(f, w);
	}
	
	auto calc_xors = [&](int start, int restricted) {
		vector<int> xors;
		
		function<void(int, int, int)> dfs = [&](int v, int p, int path_xor) {
			if (v == restricted && path_xor != 0) {
				return;
			}
			
			xors.push_back(path_xor);
			
			for (auto& [to, w] : g[v]) {
				if (to != p) {
					dfs(to, v, path_xor ^ w);
				}
			}
		};
		
		dfs(start, -1, 0);
		
		return xors;
	};
	
	auto get_ans = [&](){
		auto a_xors = calc_xors(a, b);
		
		auto b_xors = calc_xors(b, -1);
		b_xors.erase(b_xors.begin()); // can't teleport to b
		
		set<int> b_set(b_xors.begin(), b_xors.end());
		for (int a_xor : a_xors) {
			if (b_set.count(a_xor)) return true;
		}
		return false;
	};
		
	bool can = get_ans();
	cout << (can ? "YES" : "NO") << "\n";
}
	
int main() {
	int t;
	cin >> t;
	
	while (t --> 0) {
		solve_test();
	}	
	
	return 0;
}
