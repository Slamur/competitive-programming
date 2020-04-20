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

const int MODULO = 1e9 + 7;

typedef ll mod_t;

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int tests =
#ifdef ONLINE_JUDGED
		1;
#else
		ri();
#endif

	/*
	dp
	linear
	compress
	*/

	for (int t = 0; t < tests; ++t) {
		int h = ri();
		int n = ri();
		vi p = rvi(n);
		p.push_back(0);
		reverse(p.begin(), p.end());

		vi dp(n + 1, h + 1);
		dp[n] = 0;
		
		for (int i = n - 1; i >= 0; --i) {
			if (i <= n - 2) {
				if (p[i + 1] == p[i] + 1) {
					// p[i], p[i] + 1, p[i + 2]
					dp[i] = min(dp[i], dp[i + 2]);
				}
			}

			dp[i] = min(dp[i], dp[i + 1] + (i > 0));
		}

		cout << dp[0] << ENDL;
	}

	return 0;
}