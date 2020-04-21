#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const char SPACE = ' ', ENDL = '\n';

int ri() {
	int v;
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
#ifdef ONLINE_JUDGE
		1;
#else
		ri();
#endif

	/*
	#greedy
	#binary representation
	*/

	for (int t = 0; t < tests; ++t) {
		int n = ri();
		int q = ri();
		vi a = rvi(n);

		vi cnt(32, 0);
		for (int v : a) {
			int d = 0;
			while (v > 1) {
				v /= 2;
				++d;
			}

			cnt[d]++;
		}

		while (q-- > 0) {
			int query = ri();

			int ans = 0;
			for (int d = 30; d >= 0; --d) {
				int t = query / (1 << d);
				t = min(t, cnt[d]);

				query -= t * (1 << d);
				ans += t;
			}

			if (query != 0) {
				cout << -1;
			}
			else {
				cout << ans;
			}

			cout << ENDL;
		}
	}

	return 0;
}