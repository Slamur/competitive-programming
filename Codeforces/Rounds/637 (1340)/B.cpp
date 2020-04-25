#pragma comment(linker, "/STACK:66777216")

#define _USE_MATH_DEFINES

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <bitset>
#include <ctime>
#include <queue>
#include <deque>
#include <iomanip>
#include <functional>
#include <random>
#include <ctype.h>

using namespace std;

typedef uniform_int_distribution<> uid;
typedef mt19937 rnd_t;

typedef long long ll;

// need define ONLINE_JUDGE before submit
#ifdef ONLINE_JUDGE
typedef __int128_t sll;
#else
typedef ll sll;
#endif

typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<size_t> vsz;

typedef vector<ll> vll;
typedef vector<vll> vvll;

typedef vector<ii> vii;
typedef vector<vii> vvii;

typedef vector<vi> vvi;
typedef vvi graph_t;

const char SPACE = ' ', ENDL = '\n';

const int BASE = 1e9 + 7;
const int MODULO = BASE; // 1e9 + 31; //998244353

						 ///////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////

int init_input() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int local_tests =
#ifdef ONLINE_JUDGE
		1;
#else
		ri();
#endif

	return local_tests;
}

///////////////////////////////////////////////////////////////////

void read_graph(int n, int edges, graph_t & graph, bool oriented = false) {
	graph.assign(n, vi());
	for (int e = 0; e < edges; ++e) {
		int from = ri() - 1;
		int to = ri() - 1;
		graph[from].push_back(to);
		if (!oriented) graph[to].push_back(from);
	}
}

/*
tag dp
tag lexicographic
tag bitmask
*/

void solve_test() {
	vector<string> digits = {
		"1110111", // 0
		"0010010", // 1
		"1011101", // 2
		"1011011", // 3
		"0111010", // 4
		"1101011", // 5
		"1101111", // 6
		"1010010", // 7
		"1111111", // 8
		"1111011", // 9
	};

	int ml = (1 << 7);

	vvi need(ml, vi(digits.size(), -1));

	for (int mask = 0; mask < ml; ++mask) {
		for (int d = 0; d < 10; ++d) {
			int sum = 0;
			for (int b = 0; b < 7; ++b) {
				int bit = ((mask >> b) & 1);
				int db = digits[d][b] - '0';

				if (db == 0 && bit == 1) {
					sum = -1;
					break;
				}

				sum += (db != bit);
			}

			need[mask][d] = sum;
		}
	}

	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = ri();
		int k = ri();
		vector<string> s(n);
		for (int i = 0; i < n; ++i) {
			cin >> s[i];
		}

		vi masks(n);
		for (int i = 0; i < n; ++i) {
			int mask = 0;
			for (int j = 0; j < 7; ++j) {
				mask |= ((s[i][j] - '0') << j);
			}

			masks[i] = mask;
		}

		vvi dp(n + 1, vi(k + 1, false));
		dp[n][0] = true;

		for (int i = n - 1; i >= 0; --i) {
			int mask = masks[i];
			for (int j = 0; j <= k; ++j) {
				for (int d = 0; d < 10; ++d) {
					int nd = need[mask][d];
					if (nd == -1) continue;

					dp[i][j] |= (j >= nd && dp[i + 1][j - nd]);
				}
			}
		}

		if (!dp[0][k]) {
			cout << -1 << ENDL;
		}
		else {
			vi ans(n, -1);

			for (int i = 0; i < n; ++i) {
				int mask = masks[i];
				for (int d = 9; d >= 0; --d) {
					int nd = need[mask][d];
					if (nd == -1) continue;

					if (k >= nd && dp[i + 1][k - nd]) {
						ans[i] = d;
						k -= nd;
						break;
					}
				}
			}

			for (int d : ans) {
				cout << d;
			}
			cout << ENDL;
		}
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}