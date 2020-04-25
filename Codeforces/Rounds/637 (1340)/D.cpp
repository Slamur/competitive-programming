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

void read_tree(int n, graph_t & graph) {
	read_graph(n, n - 1, graph);
}

/*
tag graph
tag tree
tag path
tag constructive
*/

graph_t g;

int dt;

vii path;
vi used;

void dfs(int f = 0, int p = -1) {
	used[f] = true;

	int st = dt;
	path.push_back({ f, dt });

	int et = st - 1;

	int cs = 0;
	for (int t : g[f]) {
		if (t != p) ++cs;
	}

	int can_small = min(cs, et);
	int need_large = cs - can_small;
	
	vi & gf = g[f];

	for (int i = 0, uc = 0; i < gf.size() && uc < need_large; ++i) {
		int t = gf[i];
		if (used[t]) continue;

		++dt;
		dfs(t, f);

		++dt;
		path.push_back({ f, dt });

		++uc;
	}

	if (p != -1) {
		dt = et - can_small;
		path.push_back({ f , dt });

		for (int t : gf) {
			if (!used[t]) {
				++dt;
				dfs(t, f);

				++dt;
				path.push_back({ f, dt });
			}
		}
	}

}

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = ri();
		read_tree(n, g);

		used.assign(n, false);

		path.clear();
		dt = 0;

		int root = 0;
		dfs(root);

		cout << path.size() << ENDL;
		for (ii v : path) {
			cout << v.first + 1 << SPACE << v.second << ENDL;
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