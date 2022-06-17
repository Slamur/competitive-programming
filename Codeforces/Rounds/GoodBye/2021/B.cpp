#include <bits/stdc++.h>

int main() {
	int t;
	std::cin >> t;
	
	
	auto solve_test = [&]() {
		int n;
		std::cin >> n;
		
		std::string s;
		std::cin >> s;
		
		auto get_answer = [&]() {
			// corner case
			if (1 == n) return s + s;
			
			char beside = '\0';
			
			int last = 0;
			for (int i = 0; i < n; ++i) {
				char next = (i + 1 == n ? 'z' + 1 : s[i + 1]);
				if (s[i] > next) {
					beside = s[i];
					last = i + 1;
				} else if (s[i] < next) {
					last = i;
					break;
				} else {
					if (beside > next) {
						last = i + 1;						
					} else {
						last = i;
						break;
					}
				}
			}
			
			std::string ans = "";
			for (int i = 0; i <= last; ++i) ans += s[i];
			for (int i = last; i >= 0; --i) ans += s[i];
			
			return ans;
		};
		
		std::string answer = get_answer();
		std::cout << answer << "\n";
	};
	
	while (t --> 0) solve_test();
	
	return 0;
}
