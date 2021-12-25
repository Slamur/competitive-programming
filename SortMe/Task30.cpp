#include <bits/stdc++.h>

using ll = int64_t;

int main() {
	int n;
	std::cin >> n;
	
	std::vector<std::string> words(n);
	for (auto& word : words) std::cin >> word;
	
	ll answer = 0;
		
	std::unordered_map<int, int> mask_counts;
	
	auto get_count = [&](int mask) {
		auto it = mask_counts.find(mask);
		return (mask_counts.end() == it ? 0 : it -> second);
	};
	
	for (auto& word : words) {
		int mask = 0;
		for (char letter : word) {
			mask ^= (1 << (letter - 'a'));
		}
		
		answer += get_count(mask);
		for (int letter = 0; letter < 26; ++letter) {
			answer += get_count(mask ^ (1 << letter));
		}
		
		mask_counts[mask]++;
	}
	
	std::cout << answer << std::endl;
		
	return 0;
}
