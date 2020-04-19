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
array
sort
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
		ll k = ri();
		vi a = rvi(n);

		sort(a.begin(), a.end());

		int answer = 0;

		for (int d : a) {
			while (2 * k < d) {
				k = 2 * k;
				++answer; 
			}

			k = max(k, (ll)d);
		}

		cout << answer << endl;
	}

	return 0;
}