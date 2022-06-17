
#include <bits/stdc++.h>

using namespace std;

void init_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	cout << setprecision(10) << fixed;
}

using ll = int64_t;

void solve_test() {
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (int& v : a) cin >> v;
	
	int inf = numeric_limits<int>::max();
	
	map<int, pair<int, int>> value_to_min_d;
	map<int, int> value_to_cnt;
	
	for (int v : a) {
		value_to_min_d[v] = { inf, -1 };
		value_to_cnt[v] = 0;
	}
	
	ll ans = -inf;
	pair<ll, pair<int, int>> ans_triple = { -1, { -1, -1 } };
	
	for (int i = 0; i < n; ++i) {
		int v = a[i];
		
		value_to_cnt[v]++;
		int cnt = value_to_cnt[v];
		
		int d = 2 * cnt - i;
		
		auto d_i = pair<int, int>(d, i);
		value_to_min_d[v] = min(value_to_min_d[v], d_i);
		
		auto& [min_d, min_i] = value_to_min_d[v];
		
		ll cur_sum = d - min_d + 1;
		if (ans < cur_sum) {
			ans = cur_sum;
			ans_triple = { v, { min_i, i } };
		}
	}
	
	auto& [ans_v, ans_lr] = ans_triple;
	auto& [ans_l, ans_r] = ans_lr;
	
	cout << ans_v << " " << ans_l + 1 << " " << ans_r + 1 << "\n";
}

int main() {
	init_io();
	
	int t;
	cin >> t;
	
	while (t --> 0) {
		solve_test();
	}
	
	return 0;
}
