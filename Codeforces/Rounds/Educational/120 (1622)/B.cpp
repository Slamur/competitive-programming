#include <bits/stdc++.h>

int main() {
	int t;
	std::cin >> t;
	
	auto solve_test = []() {
		int n;
		std::cin >> n;
		
		std::vector<int> p(n);
		for (auto& v : p) std::cin >> v;
		
		std::string s;
		std::cin >> s;
		
		auto get_answer = [&]() {
			std::vector<int> pos(n + 1);
			for (int i = 0; i < n; ++i) pos[p[i]] = i;
			
			std::vector<int> q(n);
			
			int value = 1;
			for (int v = 1; v <= n; ++v) {
				int i = pos[v];
				if ('0' == s[i]) q[i] = value++;
			}
			for (int v = 1; v <= n; ++v) {
				int i = pos[v];
				if ('1' == s[i]) q[i] = value++;
			}
			return q;
		};
		
		std::vector<int> q = get_answer();
		for (int v : q) std::cout << v << " ";
		std::cout << "\n";
	};
	
	while (t --> 0) solve_test();
	
	return 0;
}
