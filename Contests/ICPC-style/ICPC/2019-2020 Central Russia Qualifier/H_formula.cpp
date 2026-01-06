#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

const mod = 1e9 + 7;

ll binpow(ll base, ll power) {
	if (power == 0) {
		return 1;
	}
	
	auto half = binpow(base, power >> 1);
	auto res = half * half;
	if (power % 2 == 1) {
		res = res * base;
	}
	
	return res;
}

ll normalize(ll& x) {
	x %= mod;
	if (x < 0) x += mod;
	return x;
}

int main() {
	ll n;
	cin >> n;
	
	auto get_answer = [&]() {
		ll res = -2 * (1 + 1) * n + 5 * binpow(3, n) - 3 * 1 - 5;
		res -= 13 * (n % 2 ? -1 : 1);
		
		normalize(res);
		s
		res *= binpow(16, mod - 2);
		
		return normalize(res);
	}	
	
	cout << get_answer() << "\n";

	return 0;
}
