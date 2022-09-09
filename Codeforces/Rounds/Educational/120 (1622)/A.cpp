#include <bits/stdc++.h>

int main() {
	int t;
	std::cin >> t;
	
	auto solve_test = []() {
		std::vector<int> lengths(3);
		for (auto& length : lengths) std::cin >> length;
		
		auto can = [&]() {
			for (int i = 0; i < 3; ++i) {
				int l1 = lengths[i], l2 = lengths[(i + 1) % 3], l3 = lengths[(i + 2) % 3];
				
				// l2 == l3, l1 = 2 * k
				if (l2 == l3 && l1 % 2 == 0) return true;
				
				// l1 = a + b; l2 == a, l3 == b
				if (l1 == l2 + l3) return true;
			}
			
			return false;
		};
		
		bool ans = can();
		std::cout << (ans ? "YES" : "NO") << "\n";
	};
	
	while (t --> 0) solve_test();
	
	return 0;
}
