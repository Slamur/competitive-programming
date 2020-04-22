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
@graph
@bfs
@prefix
@observation
*/

void solve_test() {
	int tests = ri();
	while (tests-- > 0) {
		int n = ri();
		int m = ri();
		int a = ri() - 1;
		int b = ri() - 1;
		int c = ri() - 1;
		vi p = rvi(m);

		graph_t g;
		read_graph(n, m, g);

		vector<vi> d(3, vi(n, n + 1));

		vi starts = { a, b, c };

		for (int j = 0; j < starts.size(); ++j) {
			queue<int> q;

			int start = starts[j];
			d[j][start] = 0;
			q.push(start);

			while (q.size()) {
				int f = q.front();
				q.pop();

				for (int t : g[f]) {
					if (d[j][t] > d[j][f] + 1) {
						d[j][t] = d[j][f] + 1;
						q.push(t);
					}
				}
			}
		}

		sort(p.begin(), p.end());

		vll pref(m + n + n + n + 1, 1e18);
		pref[0] = 0;
		for (int i = 0; i < m; ++i) {
			pref[i + 1] = pref[i] + p[i];
		}

		ll ans = pref[d[1][a] + d[1][c]];
		for (int v = 0; v < n; ++v) {
			int bd = d[1][v];
			ll ba = pref[bd] * 2;
			ll aca = pref[bd + d[0][v] + d[2][v]] - pref[bd];

			ans = min(ans, ba + aca);
		}

		cout << ans << ENDL;
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}