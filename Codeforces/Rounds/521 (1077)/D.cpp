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
	#array
	#counting
	#binary search
	*/

	for (int t = 0; t < tests; ++t) {
		int n = ri();
		int k = ri();
		vi a = rvi(n);

		vi cnt(2e5 + 1, 0);
		for (int v : a) cnt[v]++;

		int left = 0, right = n + 1;
		while (right - left > 1) {
			int mid = (left + right) / 2;

			int size = 0;
			for (int v = 0; v <= 2e5; ++v) {
				size += cnt[v] / mid;
			}

			if (size >= k) {
				left = mid;
			}
			else {
				right = mid;
			}
		}

		vi ans;
		for (int v = 0; v <= 2e5; ++v) {
			int delta = cnt[v] / left;
			delta = min(delta, k);

			for (int j = 0; j < delta; ++j) {
				ans.push_back(v);
			}

			k -= delta;
		}

		for (int v : ans) {
			cout << v << SPACE;
		}
		cout << ENDL;
	}

	return 0;
}