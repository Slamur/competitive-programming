#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>

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
	#long arithmetic
	*/

	for (int t = 0; t < tests; ++t) {
		int n = ri();

		string a;
		cin >> a;

		vi f = rvi(9);
		f.insert(f.begin(), 0);

		for (int i = 0; i < n; ++i) {
			int d = a[i] - '0';
			if (d < f[d]) {
				for (int j = i; j < n; ++j) {
					int dd = a[j] - '0';
					if (dd <= f[dd]) {
						a[j] = (char)(f[dd] + '0');
					}
					else {
						break;
					}
				}

				break;
			}
		}

		cout << a << endl;
	}

	return 0;
}