#include <bits/stdc++.h>

using ll = int64_t;

int main() {
	int t;
	std::cin >> t;
	
	auto solve_test = []() {
		int n;
		std::cin >> n;
		
		ll k;
		std::cin >> k;
		
		std::vector<int> a(n);
		for (auto& v : a) std::cin >> v;
		
		auto get_answer = [&]() {
			std::sort(a.begin(), a.end());
			
			std::vector<ll> pref(n + 1, 0);
			for (int i = 0; i < n; ++i) {
				pref[i + 1] = pref[i] + a[i];
			}
			
			ll smallest = a.front();
			ll ans = smallest + (n - 1);
			for (int i = 1; i <= n; ++i) {
				ll res = pref[i] - k + (n - i) * smallest;
				ll denom = (n - i + 1);
				
				if (res <= 0) res = 0;
				else res = (res - 1) / denom + 1;
				
				//std::cerr << i << " " << res << " " << pref[i] << " " << k << " " << (n - i) << " " << denom << "\n";
				
				res += (n - i);
				if (ans > res) ans = res;
			}
			
			return std::max((ll)0, ans);
		};
		
		ll ans = get_answer();
		std::cout << ans << "\n";
	};
	
	while (t --> 0) solve_test();
	
	return 0;
}
