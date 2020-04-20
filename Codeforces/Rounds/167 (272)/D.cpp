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
	combinatorics
	polynom coefficients
	map
	*/

	for (int t = 0; t < tests; ++t) {
		int n = ri();
		vi a = rvi(n);
		vi b = rvi(n);
		int m = ri();

		map<int, int> ones;
		map<int, int> twos;

		for (int i = 0; i < n; ++i) {
			if (a[i] == b[i]) {
				twos[a[i]]++;
				ones[a[i]] += 0;
			}
			else {
				ones[a[i]]++;
				ones[b[i]]++;
			}
		}

		vector<ll> facts_w2(2 * n + 1, 1);
		vector<int> tp(2 * n + 1, 0);
		vector<ll> bp(2 * n + 1, 1);

		for (int i = 1; i < tp.size(); ++i) {
			tp[i] = tp[i - 1];

			int x = i;
			while (x % 2 == 0) {
				x /= 2;
				tp[i]++;
			}

			facts_w2[i] = (facts_w2[i - 1] * x) % m;
			bp[i] = (bp[i - 1] * 2) % m;
		}

		ll ans = 1;

		for (auto & it : ones) {
			int v = it.first;
			int ov = ones[v];
			int tv = twos[v];

			int s = ov + tv * 2;

			ll num = facts_w2[s];
			int denum = tv;
			int need = tp[s] - denum;

			ans = (ans * ((num * bp[need]) % m)) % m;
		}

		cout << ans << endl;
	}

	return 0;
}