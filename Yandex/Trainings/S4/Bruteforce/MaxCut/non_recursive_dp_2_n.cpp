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
	
	int subsets = (1 << n);
	vi cuts(subsets, 0);
	
	vi v0s(subsets, 0);
	
	map<int, int> indexes;
	for (int v = 0; v < n; ++v) indexes[1 << v] = v;
	
	for (int v = 0; v < n; ++v) {
		auto& v_graph = graph[v];
		
		int total_sum = 0;
		for (int u = 0; u < v; ++u) total_sum += v_graph[u];
				
		int pref_subsets = (1 << v);
		v0s[0] = 0;
		
		for (int subset = 1; subset < pref_subsets; ++subset) {
			int prev_subset = subset & (subset - 1);
			int smallest_bit = subset ^ prev_subset;
			
			int smallest_u = indexes[smallest_bit];
			v0s[subset] = v0s[prev_subset] + v_graph[smallest_u];
		}

		for (int subset = pref_subsets - 1; subset >= 0; --subset) {
			int cut = cuts[subset];
			
			int v_0 = v0s[subset];
			int v_1 = total_sum - v_0;
			
			cuts[subset] = max(cuts[subset], cut + v_0);
			
			int v_subset = subset | (1 << v);
			cuts[v_subset] = max(cuts[v_subset], cut + v_1);
		}
	}
	
	int max_cut = -1, max_subset = -1;
	for (int subset = 0; subset < subsets; ++subset) {
		int cut = cuts[subset];
		if (max_cut < cut) {
			max_cut = cut;
			max_subset = subset;
		}	
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
