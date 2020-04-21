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
	#string
	#queries
	#window
	#prefix
	*/

	for (int t = 0; t < tests; ++t) {
		int n = ri();
		int k = ri();
		string s;
		cin >> s;

		string rgb = "RGB";

		vi cnt(3, 0);

		for (int i = 0; i < k; ++i) {
			for (int j = 0; j < 3; ++j) {
				int need = rgb[(j + i % 3) % 3];
				cnt[j] += s[i] != need;
			}
		}

		vector<char> need(3);
		for (int j = 0; j < 3; ++j) {
			need[j] = rgb[(j + k + 2) % 3];
		}

		int ans = n + 1;
		auto upd_ans = [&]() {
			ans = min(ans, min(cnt[0], min(cnt[1], cnt[2])));
		};

		upd_ans();
	
		vi nc(3, 0);
		for (int start = 1, end = start + k - 1; end < n; ++start, ++end) {
			for (int j = 0; j < 3; ++j) {
				nc[j] = cnt[(j + 2) % 3] - (s[start - 1] != s[(j + 2) % 3]) + (s[end] != need[j]);
			}

			for (int j = 0; j < 3; ++j) cnt[j] = nc[j];

			upd_ans();
		}

		cout << ans << ENDL;
	}

	return 0;
}