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
			std::map<int, int> counts;
			for (int v : a) counts[std::abs(v)]++;
			
			int answer = 0;
			for (auto& [value, count] : counts) {
				int max_distinct = 1 + (value != -value);
				answer += std::min(count, max_distinct);
			}
			
			return answer;
		};
		
		int answer = get_answer();
		std::cout << answer << "\n";
	};
	
	while (t --> 0) solve_test();
	
	return 0;
}
