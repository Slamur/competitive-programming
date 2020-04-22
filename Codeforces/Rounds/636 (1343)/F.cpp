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
	@permutation
	@construction
	@observation
	*/


	bool fourth = false;
	for (int t = 0; t < tests; ++t) {
		int n = ri();
		vector<vi> a(n - 1, vi());
		for (int i = 0; i < n - 1; ++i) {
			int sz = ri();
			a[i] = rvi(sz);
		}

		vector<vi> in(n - 1, vi(n + 1, false));
		for (int i = 0; i < a.size(); ++i) {
			for (int v : a[i]) in[i][v] = true;
		}

		vi oc(n + 1, 0);
		for (auto & row : a) {
			for (int v : row) {
				oc[v]++;
			}
		}

		vi pl;
		for (int i = 1; i <= n; ++i) {
			if (oc[i] == 1) {
				pl.push_back(i);
			}
		}

		vi ans(n, 0);
		for (int last : pl) {
			vi cnts(oc.begin(), oc.end());

			vi used(n - 1, false);

			ans.assign(n, -1);

			bool fail = false;

			vi pc;
			pc.push_back(last);

			for (int j = n - 1; j >= 0; --j) {
				int cur = -1;
				for (int v : pc) {
					if (cnts[v] <= 1) {
						if (cur == -1 || oc[cur] < oc[v]) cur = v;
					}
				}

				ans[j] = cur;
					
				if (ans[j] == -1) {
					fail = true;
					break;
				}

				pc.clear();
				for (int i = 0; i < n - 1; ++i) {
					if (!used[i] && in[i][ans[j]]) {
						for (int v : a[i]) {
							cnts[v]--;
							if (v != ans[j] && cnts[v] <= 1) pc.push_back(v);
						}

						used[i] = true;
					}
				}
			}

			if (!fail) break;
		}

		for (int v : ans) {
			cout << v << SPACE;
		}
		cout << ENDL;
	}

	return 0;
}