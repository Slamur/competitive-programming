#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
	int n;
	cin >> n;
	
	string s;
	cin >> s;
	
	auto get_answer = [&]() {
		const int one = '1', zero = '0';
	
		int first_one = -1;
		for (int i = 0; i < n; ++i) {
			if (one == s[i]) {
				first_one = i;
				break;
			}
		}
			
		if (-1 == first_one) {
			return string(1, '0');
		}
		
		string large_s = s.substr(first_one, n - first_one);
		
		int first_zero_after = -1;
		for (int i = 0; i < large_s.size(); ++i) {
			if (zero == large_s[i]) {
				first_zero_after = i;
				break;
			}
		}
		
		if (first_zero_after == -1) {
			return large_s;
		}
		
		vector<int> large(large_s.size());
		for (int i = 0; i < large.size(); ++i) large[i] = large_s[i] - zero;
		
		vector<int> best = large;
		for (int start = 0; start < first_zero_after; ++start) {
			vector<int> cur = large;
			for (int i = first_zero_after, j = start; i < large.size(); ++i, ++j) {
				cur[i] |= large[j];
			}
			best = max(best, cur);
		}
		
		string best_s;
		for (int bit : best) best_s += (char)(bit + zero);
		
		return best_s;
	};
	
	cout << get_answer() << "\n";

	return 0;
}
