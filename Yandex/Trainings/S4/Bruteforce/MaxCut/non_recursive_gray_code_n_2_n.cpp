#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

int get_bit(int mask, int bit) {
	return (mask >> bit) & 1;
}

void solve() {
	int n;
	cin >> n;
	
	vector<vi> graph(n, vi(n));
	for (auto& row : graph) for (auto& edge : row) cin >> edge;
	
	map<int, int> indexes;
	for (int v = 0; v < n; ++v) indexes[1 << v] = v;
	
	int cut = 0;
	int prev_subset = 0;
	
	int max_cut = cut, max_subset = prev_subset;
	
	int subsets = (1 << n) >> 1;
	
	for (int i = 1; i < subsets; ++i) {
		int subset = i ^ (i >> 1);
		
		int diff_bit = subset ^ prev_subset;
		int diff_v = indexes[diff_bit];
		
		int v_part = get_bit(subset, diff_v);
	
		auto& v_graph = graph[diff_v];
		for (int u = 0; u < n; ++u) {
			int w_delta = v_graph[u];
			cut += get_bit(subset, u) == v_part ? -w_delta : w_delta;
		} 
		
		if (max_cut < cut) {
			max_cut = cut;
			max_subset = subset;
		}
		
		prev_subset = subset;
	}
	
	cout << max_cut << "\n";
	for (int v = 0; v < n; ++v, max_subset >>= 1) {
		int part = max_subset & 1;
		cout << part + 1 << " ";
	}
	cout << "\n";
}

int main() {
	solve();
	return 0;
}
