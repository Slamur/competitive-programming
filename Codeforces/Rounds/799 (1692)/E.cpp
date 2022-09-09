
#include <bits/stdc++.h>

using namespace std;

void init_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	cout << setprecision(10) << fixed;
}

using ll = int64_t;

void solve_test() {
	int n, s;
	cin >> n >> s;
	
	vector<int> a(n);
	for (int& v : a) cin >> v;
	
	auto get_ans = [&]() {		
		vector<ll> pref(n + 1, 0);
		for (int i = 0; i < n; ++i) {
			pref[i + 1] = pref[i] + a[i];
		}
		
		vector<int> lefts(n + 1, n + 1);
		vector<int> rights(n + 1, -1);
		
		for (int i = 0; i <= n; ++i) {
			rights[pref[i]] = i;
		}
		
		for (int i = n; i >= 0; --i) {
			lefts[pref[i]] = i;
		}
		
		int best = 0;
		for (int rs = s; rs <= n; ++rs) {
			int ls = rs - s;
			
			int cur = rights[rs] - lefts[ls];
			best = max(best, cur);
		}
		
		if (0 == best) return -1;
		return n - best;
	};
	
	cout << get_ans() << "\n";
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
