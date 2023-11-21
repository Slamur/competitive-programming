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
	
	map<int, int> indexes;
	for (int v = 0; v < n; ++v) indexes[1 << v] = v;
	
	for (int v = 0; v < n; ++v) {
		auto& v_graph = graph[v];
		
		int total_sum = 0;
		for (int u = 0; u < v; ++u) total_sum += v_graph[u];
				
		int pref_subsets = (1 << v);
		
		for (int subset = 0; subset < pref_subsets; ++subset) {
			cuts[subset | (1 << v)] = cuts[subset];
		}
		
		int v_0 = 0;
		int prev_subset = 0;
		cuts[1 << v] += total_sum;
		
		for (int i = 1; i < pref_subsets; ++i) {
			int subset = i ^ (i >> 1);
			
			int diff_bit = subset ^ prev_subset;
			int diff_u = indexes[diff_bit];
		
			int w_delta = v_graph[diff_u];
			v_0 += get_bit(subset, diff_u) ? w_delta : -w_delta;
			
			cuts[subset] += v_0;
			cuts[subset | (1 << v)] += total_sum - v_0;
			
			prev_subset = subset;
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
