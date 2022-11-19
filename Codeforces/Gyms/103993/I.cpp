#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
	int n, need;
	ll last_x;
	cin >> n >> need >> last_x;
	
	vector<int> stands(n);
	for (auto& x : stands) cin >> x;
	sort(stands.begin(), stands.end());
	
	ll first_x = 0;
	
	auto can = [&](ll power) {
		ll max_light_x = first_x + power;
		ll max_covered = -1;
		
		int used = 0;
		int last_possible = -1;
		for (int x : stands) {
			if (x <= max_light_x) {
				last_possible = x;
			} else {
				if (last_possible > max_light_x) return false;
				
				++used;
				max_covered = last_possible + power;
				max_light_x = max_covered + power;
				last_possible = x;
			}
		}
		
		if (max_covered < last_x && last_possible <= max_light_x) {
			++used;
			max_covered = last_possible + power;
			max_light_x = max_covered + power;
			last_possible = -1;
		}
		
		return used <= need && max_covered >= last_x;
	};
	
	ll left = 0, right = last_x;
	while (right - left > 1) {
		ll mid = (left + right) / 2;
		
		if (can(mid)) right = mid;
		else left = mid;
	}
	
	cout << right << "\n";

	return 0;
}
