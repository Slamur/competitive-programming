#include <bits/stdc++.h>

int main() {
	int n, k;
	std::cin >> n >> k;
	
	std::vector<std::pair<int, int>> queries(n);
	for (auto& [a, b] : queries) std::cin >> a >> b;
	
	std::vector<bool> is_prime(k + 1, true);
	is_prime[0] = is_prime[1] = false;
	for (int i = 2; i * i <= k; ++i) {
		if (is_prime[i]) {
			for (int j = i * i; j <= k; j += i) is_prime[j] = false;
		}
	}
	
	std::vector<int> pref(k + 1, 0);
	for (int i = 1; i <= k; ++i) {
		pref[i] = pref[i - 1] + is_prime[i];
	}
	
	for (auto& [a, b] : queries) {
		std::cout << pref[std::max(a, b)] - pref[std::min(a, b) - 1] << "\n";
	}
		
	return 0;
}

