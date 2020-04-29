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

void read_graph(int n, int edges, graph_t & graph, bool oriented = false) {
	graph.assign(n, vi());
	for (int e = 0; e < edges; ++e) {
		int from = ri() - 1;
		int to = ri() - 1;
		graph[from].push_back(to);
		if (!oriented) graph[to].push_back(from);
	}
}

bool yn(bool result) {
	cout << (result ? "YES" : "NO") << ENDL;
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
	FILE * tmp_in;
	freopen_s(&tmp_in, "input.txt", "r", stdin);

	FILE * tmp_out;
	freopen_s(&tmp_out, "output.txt", "w", stdout);
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
tag graph
tag tree
tag degree
tag construction
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = ri();
		int t = ri();
		int k = ri();

		vi a = rvi(t);
		a.insert(a.begin(), 1);

		int root = 0;

		vvi layers(t + 1, vi());
		vi li(n, 0);
		for (int i = 0, v = 0; i <= t; ++i) {
			for (int j = 0; j < a[i]; ++j, ++v) {
				layers[i].push_back(v);
				li[v] = i;
			}
		}

		graph_t g(n, vi());
		vi parents(n, -1);
		for (int i = 1; i <= t; ++i) {
			for (int j = 0; j < a[i]; ++j) {
				int v = layers[i][j];
				int p = layers[i - 1][j < a[i - 1] ? j : 0];

				g[v].push_back(p);
				g[p].push_back(v);
				parents[v] = p;
			}
		}

		int leafs = 0;
		for (int v = 0; v < n; ++v) {
			if (root == v) continue;
			if (1 == g[v].size()) ++leafs;
		}

		for (int i = 1; i < t; ++i) {
			int first = layers[i].front();
			
			for (int j = 1; j < a[i]; ++j) {
				int v = layers[i][j];

				if (leafs < k && g[v].size() > 1) {
					int p = parents[v];
					for (int ch : g[v]) {
						if (li[ch] == i - 1) continue; // old parent
							
						parents[ch] = first;
					}

					++leafs;
				}
			}
		}

		if (leafs != k) {
			cout << -1 << ENDL;
		}
		else {
			cout << n << ENDL;
			for (int v = 0; v < n; ++v) {
				int p = parents[v];
				if (p != -1) {
					cout << p + 1 << SPACE << v + 1 << ENDL;
				}
			}
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