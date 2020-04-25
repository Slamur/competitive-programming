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
tag graph
tag bfs 0-k
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = ri();
		int m = ri();

		vi d = rvi(m);

		int g = ri();
		int r = ri();

		sort(d.begin(), d.end());

		vi prev(m, g + r + 1);
		vi next(m, g + r + 1);

		for (int i = 0; i < m; ++i) {
			if (i > 0) {
				prev[i] = d[i] - d[i - 1];
			}

			if (i + 1 < m) {
				next[i] = d[i + 1] - d[i];
			}
		}

		const int MAX_M = 1e4 + 10;
		vector<bitset<MAX_M>> was(g + 1, bitset<MAX_M>());

		vector<queue<int>> q(g + 1, queue<int>());

		was[0][0] = true;
		q[0].push(0);

		vll answers(g + 1, LLONG_MAX);

		for (ll it = 0; q[0].size(); ++it) {
			int st = it * (r + g);

			for (int time = 0; time < g; ++time) {
				queue<int> & qt = q[time];

				while (qt.size()) {
					int f = qt.front();
					qt.pop();

					if (f == m - 1) {
						answers[time] = st + time;
					}

					{
						int t = f - 1;
						int nt = time + prev[f];

						if (nt <= g) {
							if (!was[nt][t]) {
								was[nt][t] = true;
								q[nt].push(t);
							}
						}
					}

					{
						int t = f + 1;
						int nt = time + next[f];
						if (nt <= g) {
							if (!was[nt][t]) {
								was[nt][t] = true;
								q[nt].push(t);
							}
						}
					}
				}
			}

			queue<int> & ql = q[g];
			queue<int> & qf = q[0];
			while (ql.size()) {
				int f = ql.front();
				ql.pop();

				qf.push(f);

				if (f == m - 1) {
					answers[g] = st + g;
				}
			}
		}

		ll answer = LLONG_MAX;
		for (ll time : answers) {
			answer = min(answer, time);
		}

		if (LLONG_MAX == answer) answer = -1;
		cout << answer << ENDL;
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}