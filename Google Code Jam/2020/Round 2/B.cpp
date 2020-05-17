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
#include <fstream>
#include <ctype.h>

using namespace std;

typedef uniform_int_distribution<> uid;
typedef mt19937 rnd_t;

typedef long long ll;

// need define ONLINE_JUDGE before submit
//#ifdef ONLINE_JUDGE
//typedef __int128_t sll;
//#else
//typedef ll sll;
//#endif

typedef pair<int, int> ii;

typedef vector<int> vi;
typedef vector<size_t> vsz;

typedef vector<ll> vll;
typedef vector<vll> vvll;

typedef vector<ii> vii;
typedef vector<vii> vvii;

typedef vector<vi> vvi;
typedef vvi graph_t;

typedef vector<bool> vb;
typedef vector<vb> vvb;

const char SPACE = ' ', ENDL = '\n';

const int BASE = (int)1e9 + 7;
const int MODULO = BASE; // 1e9 + 31; //998244353

typedef ll mod_t;

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

string rs() {
	string s;
	cin >> s;
	return s;
}

vi rvi(int n) {
	vi a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	return a;
}

void read_graph(int n, int edges, graph_t& graph, bool oriented = false) {
	graph.assign(n, vi());
	for (int e = 0; e < edges; ++e) {
		int from = ri() - 1;
		int to = ri() - 1;
		graph[from].push_back(to);
		if (!oriented) graph[to].push_back(from);
	}
}

bool yn(bool result, string yes = "YES", string no = "NO") {
	cout << (result ? yes : no) << ENDL;
	return result;
}

//////////////////////////////////////////////////////////////////

int get_bit(int mask, int bit) {
	return (mask >> bit) & 1;
}

//////////////////////////////////////////////////////////////////

// taken from https://codeforces.com/blog/entry/76149?#comment-606512

//template<class... args>
//auto create(size_t n, args&&... args) {
//	if (constexpr(sizeof...(args) == 1)) {
//		return vector(n, args...);
//	}
//	else
//	{
//		return vector(n, create(args...));
//	}	
//}

//////////////////////////////////////////////////////////////////

int init_input() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

#ifndef ONLINE_JUDGE
	FILE* tmp_in;
	freopen_s(&tmp_in, "input.txt", "r", stdin);

	FILE* tmp_out;
	freopen_s(&tmp_out, "output.txt", "w", stdout);
#endif

	cout << setprecision(10) << fixed;

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
tag graph
tag weighted graph
tag shortest path
tag sort
tag construction
*/

void solve_test() {
	int tests = ri();
	for (int test = 1; test <= tests; ++test) {
		cout << "Case #" << test << ": ";

		int n = ri();
		int m = ri();

		vi x = rvi(n - 1);
		x.insert(x.begin(), 0);

		vii edges(m);

		vector<vii> graph(n, vii(0));
		for (int e = 0; e < m; ++e) {
			int from = ri() - 1;
			int to = ri() - 1;

			edges[e] = { from, to };
			graph[from].push_back({ to, e });
			graph[to].push_back({ from, e });
		}

		int start = 0;

		vii unknown;
		vii known;

		for (int i = 0; i < n; ++i) {
			if (x[i] < 0) {
				// unknown
				unknown.push_back({ -x[i], i });
			}
			else {
				known.push_back({ x[i], i });
			}
		}

		sort(unknown.begin(), unknown.end());
		sort(known.begin(), known.end());

		vi times(n, 1e6);
		for (auto& k : known) {
			times[k.second] = k.first;
		}

		vi us(unknown.size(), 0);
		for (int u = 1; u < unknown.size(); ++u) {
			us[u] = u;
			if (unknown[u].first == unknown[u - 1].first) {
				us[u] = us[u - 1];
			}
		}

		for (int u = 0; u < unknown.size(); ++u) {
			int v = unknown[u].second;
			int smaller = unknown[u].first;

			int unknownSmaller = us[u];
			int knownSmaller = smaller - unknownSmaller;

			int lastUnknown = (0 == unknownSmaller ? -1 : times[unknown[unknownSmaller - 1].second]);
			int lastKnown = times[known[knownSmaller - 1].second];

			times[v] = max(lastUnknown, lastKnown) + 1;
		}

		vi answer(m);
		for (int v = 0; v < n; ++v) {
			for (auto& edge : graph[v]) {
				int to = edge.first;
				int e = edge.second;

				ll weight = max(abs(times[v] - times[to]), 1);
				answer[e] = weight;
			}
		}

		for (int w : answer) {
			cout << w << SPACE;
		}
		cout << ENDL;
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}