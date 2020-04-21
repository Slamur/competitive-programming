#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include <set>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const char SPACE = ' ', ENDL = '\n';

int ri() {
	int v;
	cin >> v;
	return v;
}

ll rll() {
	ll v;
	cin >> v;
	return v;
}

vi rvi(int n) {
	vi a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	return a;
}

const int MODULO = 1e9 + 7;

typedef ll mod_t;

inline mod_t add(mod_t a, mod_t b) {
	return (a + b) % MODULO;
}

inline void add_to(mod_t & a, mod_t b) {
	a += b;
	if (a >= MODULO) a -= MODULO;
}

inline mod_t subtract(mod_t a, mod_t b) {
	return add(a, MODULO - b);
}

inline void subtract_from(mod_t & a, mod_t b) {
	a -= b;
	if (a < 0) a += MODULO;
}

inline mod_t multiply(mod_t a, mod_t b) {
	return ((a * b) % MODULO);
}

mod_t binpow(int base, ll power) {
	if (power == 0) return 1;

	ll result = binpow(base, power >> 1);
	result = multiply(result, result);

	if (power & 1) {
		result = multiply(result, base);
	}

	return result;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int tests =
#ifdef ONLINE_JUDGE
		1;
#else
		ri();
#endif

	/*
	#number theory
	#prime number
	#modular arithmetic
	#factorial
	#factorial prime power
	*/

	for (int t = 0; t < tests; ++t) {
		int x = ri();
		ll n = rll();	

		vector<ll> pr;

		for (int p = 2; p * p <= x; ++p) {
			if (x % p == 0) {
				pr.push_back(p);
				while (x % p == 0) x /= p;
			}
		}
		
		if (x > 1) pr.push_back(x);

		mod_t ans = 1;

		for (ll p : pr) {
			ll pow = 0;
			
			ll s = n;
			while (s != 0) {
				pow += s / p;
				s /= p;
			}

			ans = multiply(ans, binpow(p, pow));
		}

		cout << ans << endl;
	}

	return 0;
}