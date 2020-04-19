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

/**
graph
shortest path
minimal spanning tree
prime
constructive
*/

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

	for (int t = 0; t < tests; ++t) {
		int n = ri();
		int m = ri();

		auto is_prime = [&](int x) {
			if (x == 1) return false;

			for (int d = 2; d * d <= x; ++d) if (x % d == 0) return false;

			return true;
		};

		int sp = n - 1;
		while (!is_prime(sp)) ++sp;

		cout << sp << " " << sp << endl;

		for (int i = 0; i < n - 2; ++i) {
			cout << (i + 1) << " " << (i + 2) << " " << 1 << ENDL;
		}

		int last_edge = sp - (n - 2);
		cout << (n - 1) << " " << n << " " << last_edge << ENDL;

		for (int i = n - 1, x = 1, y = 1; i < m; ++i) {
			while (y <= x + 1) {
				++y;
				if (y == n + 1) {
					y = 1;
					++x;
				}
			}

			cout << x << " " << y << " " << sp + 1 << ENDL;
			++y;
			if (y == n + 1) {
				y = 1;
				++x;
			}
		}
	}

	return 0;
}