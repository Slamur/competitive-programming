#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
	int n;
	cin >> n;
	
	vector<ll> a(n);
	for (auto& v : a) cin >> v;
	
	multiset<ll> ms(a.begin(), a.end());
	for (int it = 0; it < n - 1; ++it) {
		auto left_it = ms.begin();
		auto right_it = prev(ms.end());
		
		ll new_score = (*left_it + *right_it) / 2;
		ms.erase(left_it);
		ms.erase(right_it);
		ms.insert(new_score);
	}
	
	ll ans = *ms.begin();
	cout << ans << "\n";

	return 0;
}
