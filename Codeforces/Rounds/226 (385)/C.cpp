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
tag number theory
tag prime numbers
tag sieve
tag prefix sums
tag queries
*/

void solve_test() {
	int tests = 1;// ri();
	while (tests-- > 0) {
		int n = ri();
		vi a = rvi(n);

		const int maxV = 1e7;
		vi cnt(maxV + 1, 0);

		for (int v : a) cnt[v]++;

		vector<char> p(maxV + 1, true);
		vi pref(maxV + 2, 0);

		for (int d = 2; d <= maxV; ++d) {
			if (!p[d]) continue;

			pref[d] = cnt[d];
			for (int j = d + d; j <= maxV; j += d) {
				p[j] = false;
				pref[d] += cnt[j];
			}
		}

		for (int v = 1; v < pref.size(); ++v) {
			pref[v] += pref[v - 1];
		}

		int q = ri();
		while (q-- > 0) {
			int l = ri();
			int r = ri();

			if (l > maxV) l = maxV + 1;
			if (r > maxV) r = maxV + 1;

			int ans = pref[r] - pref[l - 1];
			cout << ans << ENDL;
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