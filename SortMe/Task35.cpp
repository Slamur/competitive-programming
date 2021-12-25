#include <bits/stdc++.h>

int main() {
	int n, k;
	std::cin >> n >> k;
	
	std::vector<std::pair<int, int>> players(n);
	for (auto& [w, a] : players) std::cin >> w >> a;
	
	int block_size = n / k;
	
	std::vector<std::vector<int>> gambles_by_side(k);
	for (auto& [w, a] : players) gambles_by_side[w - 1].push_back(a);
	
	int sum = 0;
	for (auto& [w, a]: players) sum += a;
	
	for (auto& gambles : gambles_by_side) {
		sort(gambles.rbegin(), gambles.rend());
		for (size_t i = block_size * (k - 1); i < gambles.size(); ++i) {
			sum -= (k + 1) * gambles[i];
		}
	}
	
	std::cout << sum << std::endl;
		
	return 0;
}

