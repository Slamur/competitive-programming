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
tag bitmask
*/

void solve_test() {
	int tests = 1;// ri();
	while (tests-- > 0) {
		int n = ri();
		int m = ri();

		vector<string> rows(n);
		for (int i = 0; i < n; ++i) cin >> rows[i];

		auto path = [&](int i) {
			return min(i, m - i);
		};


		const int D = 0, L = 1, S = 2;

		auto type = [&](char ch) {
			if (isdigit(ch)) return D;
			if (isalpha(ch)) return L;
			return S;
		};

		vvi a(3, vi(n, n * m + 1));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				char ch = rows[i][j];
				int p = path(j);

				int t = type(ch);
				a[t][i] = min(a[t][i], p);
			}
		}

		vvi dp(n + 1, vi(1 << 3, n * m + 1));
		dp[0][0] = 0;

		for (int i = 0; i < n; ++i) {
			for (int mask = 0; mask < (1 << 3); ++mask) {
				dp[i + 1][mask] = min(dp[i + 1][mask], dp[i][mask]);

				for (int cur = 0; cur < 3; ++cur) {
					dp[i + 1][mask | (1 << cur)] = min(
						dp[i + 1][mask | (1 << cur)],
						dp[i][mask] + a[cur][i]
					);
				}
			}
		}

		cout << dp[n][7] << ENDL;
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}