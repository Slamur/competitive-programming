#include <bits/stdc++.h>

int main() {
	int t;
	std::cin >> t;
	
	
	auto solve_test = [&]() {
		int n;
		std::cin >> n;
		
		std::vector<int> a(n);
		for (int& v : a) std::cin >> v;
		
		auto get_answer = [&]() {
			int answer = std::max(0, n - 2);
			for (int left = 0; left < n; ++left) {
				for (int right = left + 1; right < n; ++right) {
					int count = 0;
					for (int k = 0; k < n; ++k) {
						if ((a[k] - a[left]) * (right - left) != (a[right] - a[left]) * (k - left)) {
							++count;
						}
					}
					answer = std::min(answer, count);
				}
			}
			
			return answer;
		};
		
		int answer = get_answer();
		std::cout << answer << "\n";
	};
	
	while (t --> 0) solve_test();
	
	return 0;
}
