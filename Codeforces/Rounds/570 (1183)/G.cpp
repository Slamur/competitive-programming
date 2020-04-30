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

struct DSU {
	vector<size_t> parents;
	vector<size_t> ranks;
	vi is_cycles;

	DSU(vi& degrees) {
		resize(degrees);
	}

	void resize(vi& degrees) {
		size_t n = degrees.size();

		parents.resize(n);
		for (size_t v = 0; v < n; ++v) {
			parents[v] = v;
		}

		ranks.resize(n, 1);

		is_cycles.resize(n, true);
		for (size_t v = 0; v < n; ++v) {
			is_cycles[v] = (2 == degrees[v]);
		}
	}

	size_t get(size_t v) {
		size_t parent = parents[v];
		if (parent == v) return v;

		return parents[v] = get(parent);
	}

	bool merge(size_t f, size_t t) {
		size_t a = get(f);
		size_t b = get(t);

		if (a == b) return false;

		if (ranks[a] < ranks[b]) {
			swap(a, b);
		}

		parents[b] = a;
		if (ranks[a] == ranks[b]) ++ranks[a];

		is_cycles[a] &= is_cycles[b];

		return true;
	}

	bool connected(size_t f, size_t t) {
		return get(f) == get(t);
	}

	bool is_root(size_t v) {
		return get(v) == v;
	}

	bool is_cycle(size_t v){
		return is_cycles[v];
	}
};


/*
tag data structures
tag priority queue
tag multitest
*/

void solve_test() {
	int tests = ri();
	while (tests-- > 0) {
		int n = ri();
		vii a(n);

		for (int i = 0; i < n; ++i) {
			a[i].first = ri() - 1;
			a[i].second = ri();
		}

		vi cnts(n, 0);
		vi zeros(n, 0);

		for (ii& candy : a) {
			cnts[candy.first]++;
			zeros[candy.first] += 1 - candy.second;
		}

		vvi ones_by_cnts(n + 1, vi(0));
		for (int type = 0; type < n; ++type) {
			if (cnts[type] > 0) {
				ones_by_cnts[cnts[type]].push_back(zeros[type]);
			}
		}

		priority_queue<int, vector<int>, greater<int>> waiting;
		
		ll total = 0;
		ll total_ones = 0;

		for (int cnt = n; cnt > 0; --cnt) {
			for (int one : ones_by_cnts[cnt]) {
				waiting.push(one + (n - cnt));
			}

			if (waiting.size() > 0) {
				int one = max(0, waiting.top() - (n - cnt));
				waiting.pop();

				total += cnt;
				total_ones += one;
			}
		}

		cout << total;
		cout << SPACE << total - total_ones;
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