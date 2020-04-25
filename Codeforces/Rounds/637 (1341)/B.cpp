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

void read_graph(int n, int edges, graph_t & graph, bool oriented = false) {
	graph.assign(n, vi());
	for (int e = 0; e < edges; ++e) {
		int from = ri() - 1;
		int to = ri() - 1;
		graph[from].push_back(to);
		if (!oriented) graph[to].push_back(from);
	}
}

void yn(bool result) {
	cout << (result ? "YES" : "NO") << ENDL;
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

/*
tag multitest
tag array
tag prefix
tag window
tag local maximum
*/

void solve_test() {
	int tests = ri();
	while (tests-- > 0) {
		int n = ri();
		int k = ri();
		vi a = rvi(n);

		a.insert(a.begin(), INT_MAX);
		a.push_back(INT_MAX);

		vi pref(a.size(), 0);
		for (int i = 1; i <= n; ++i) {
			pref[i] = pref[i - 1];
			if (a[i - 1] < a[i] && a[i] > a[i + 1]) {
				pref[i]++;
			}
		}

		ii answer(-1, -1);

		for (int start = 1, end = start + k - 1; end <= n; ++start, ++end) {
			int cnt = pref[end - 1] - pref[start];
			if (answer.first < cnt) {
				answer.first = cnt;
				answer.second = start;
			}
		}

		cout << answer.first + 1 << SPACE << answer.second << ENDL;
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}