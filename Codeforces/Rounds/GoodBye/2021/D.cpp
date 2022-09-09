#include <bits/stdc++.h>

using ll = int64_t;

#define NSTRESS

using uid = std::uniform_int_distribution<>;
using rnd_t = std::mt19937;

int main() {
	int t;
	#ifndef STRESS
		std::cin >> t;
	#else
		t = 1000;
	#endif
	
	#ifdef STRESS
		ll seed = 12345;
		bool with_time = false;//true;
		if (with_time) seed += time(0);
		rnd_t rnd(seed);
	
		uid nGen(1, 10);
		uid aGen(-100, 100);
		uid xGen(-100, 100);
	#endif
	
	
	
	auto solve_test = [&]() {
		
		int n;
		#ifndef STRESS
			std::cin >> n;
		#else
			n = nGen(rnd);
		#endif
		
		std::vector<ll> a(n);
		#ifndef STRESS
			for (auto& v : a) std::cin >> v;
		#else
			for (int i = 0; i < n; ++i) a[i] = aGen(rnd);
		#endif
		
		ll x;
		#ifndef STRESS
			std::cin >> x;
		#else
			x = xGen(rnd);
		#endif
		
		auto get_answer = [&]() {
			std::vector<ll> pref(n + 1, 0);
			for (int i = 0; i < n; ++i) {
				pref[i + 1] = pref[i] + a[i];
			}
			
			std::vector<ll> d(pref.size(), 0);
			for (int i = 0; i < (int)pref.size(); ++i) {
				d[i] = pref[i] - i * x;
			}
			
			int answer = 0;
			
			//std::multiset<std::pair<ll, int>> pref_d;
			
			int start = 0;
			for (int i = 0; i < (int)d.size(); ++i) {
				//pref_d.insert({d[i], i});
				
				bool good = true;
				if (i - 2 >= start) good &= d[i] >= d[i - 2];
				if (i - 3 >= start) good &= d[i] >= d[i - 3];
				
				if (!good) {
					++answer;
					start = i;
					
					/*auto min_it = pref_d.begin();
					
					int min_i = min_it -> second;
					int new_start = min_i + 1;
					
					for (; start < new_start; ++start) {
						auto it = pref_d.find({d[start], start});
						pref_d.erase(it);
					}*/
				}
			}
			
			return n - answer;
		};
		
		auto get_brute_answer = [&]() {
			int ans = 0;
			for (int mask = 0; mask < (1 << n); ++mask) {
				std::vector<bool> used(n, false);
				for (int bit = 0; bit < n; ++bit) {
					if ((mask >> bit) & 1) used[bit] = true;
				}
				
				bool can = true;
				for (int left = 0; left < n; ++left) {
					for (int right = left + 1; right < n; ++right) {
						
						bool hole = false;
						for (int k = left; k <= right; ++k) hole |= used[k];
						
						if (hole) continue;
						
						ll sum = 0;
						for (int k = left; k <= right; ++k) sum += a[k];
						
						can &= (sum >= (right - left + 1) * x);
					}
				}
				
				if (can) {
					int res = 0;
					for (int i = 0; i < n; ++i) {
						if (!used[i]) ++res;
					}
					
					ans = std::max(ans, res);
				}
			}
			
			return ans;
		};
		
		int answer = get_answer();
		#ifndef STRESS
		std::cout << answer << "\n";
		#else
		int brute_answer = get_brute_answer();
		if (answer != brute_answer) {
			std::cerr << "Gotcha!" << "\n";
			std::cerr << n << "\n";
			for (int v : a) std::cerr << v << " ";
			std::cerr << "\n" << x << "\n";
			
			std::cerr << answer << " " << brute_answer << "\n";
			return false;
		}
		#endif
		return true;
	};
	
	while (t --> 0) {
		if (!solve_test()) break;
	}
	
	return 0;
}
