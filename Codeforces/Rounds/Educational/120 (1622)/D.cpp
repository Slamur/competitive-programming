#include <bits/stdc++.h>

using ll = int64_t;

using mod_t = ll;

const mod_t MOD = 998244353;

mod_t add(mod_t a, mod_t b) {
	return (a + b) % MOD;
}

mod_t sub(mod_t a, mod_t b) {
	return add(a, MOD - b);
}

int main() {
	int t;
	//std::cin >> t;
	t = 1;
	
	const int MAX_N = 5000;
	std::vector<std::vector<mod_t>> c(MAX_N + 1);
	for (int i = 0; i <= MAX_N; ++i) {
		c[i].resize(i + 1);
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
		}
	}
	
	auto solve_test = [&]() {
		int n;
		std::cin >> n;
		
		int k;
		std::cin >> k;
		
		std::string s;
		std::cin >> s;
		
		auto get_answer = [&]() -> ll {
			// take only 0
			if (0 == k) return 1;
			
			std::vector<int> blocks;
			int block = 0;
			
			for (int i = 0; i < n; ++i) {
				if ('1' == s[i]) {
					blocks.push_back(block);
					block = 0;
				} else {
					block++;
				}
			}
			
			blocks.push_back(block);
			
			int size = blocks.size();
			std::vector<int> pref(size + 1, 0);
			
			for (int i = 0; i < size; ++i) pref[i + 1] = pref[i] + blocks[i];
			
			// cnt(1) < k
			int ones_count = n - pref.back();
			if (ones_count < k) return 1;
			
			ll ans = 0;
			
			for (int i = k + 1; i <= size; ++i) {
				ans = add(ans, c[k + pref[i] - pref[i - (k + 1)]][k]);
				if (i > k + 1) ans = sub(ans, c[k - 1 + pref[i - 1] - pref[i - (k + 1)]][k - 1]);
			}
			
			return ans;
		};
		
		ll ans = get_answer();
		std::cout << ans << "\n";
	};
	
	while (t --> 0) solve_test();
	
	return 0;
}
