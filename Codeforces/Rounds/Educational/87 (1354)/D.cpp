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

class FenwickTree {

	size_t size;
	vll t;
	vll values;

public:
	FenwickTree(size_t n)
		: size(n + 1)
		, t(size, 0LL)
		, values(size, 0LL)
	{ }

	void update_tree_index(int index, ll delta) {
		for (; (size_t)index < size; index += index & -index) {
			t[index] += delta;
		}
	}

	void update_value(size_t index, ll value) {
		ll delta = value - values[index + 1];
		increase_value(index, delta);
	}

	void increase_value(size_t index, ll delta) {
		++index;
		values[index] += delta;

		update_tree_index(index, delta);
	}

	ll get_prefix_sum(int index) {
		++index;

		ll sum = 0;
		for (; index > 0; index -= index & -index) {
			sum += t[index];
		}

		return sum;
	}

	pair<size_t, ll> get_max_prefix_lower(ll value) {
		size_t result = 0;
		ll sum = 0;

		for (int bit = 20; bit >= 0; --bit) {
			size_t next = result | (1 << bit);
			if (next < size && sum + t[next] < value) {
				result = next;
				sum += t[next];
			}
		}

		return { result, sum };
	}

	void clear() {
		t.assign(size, 0LL);
		values.assign(size, 0LL);
	}
};


/*
tag queries
tag array
tag fenwick
tag k-th element
tag multiset
*/

void solve_test() {
	int tests = 1;
	for (int test = 1; test <= tests; ++test) {
		int n = ri();
		int q = ri();

		FenwickTree tree(n + 1);

		for (int i = 0; i < n + q; ++i) {
			int query = ri();
			if (query > 0) {
				tree.increase_value(query, 1);
			}
			else {
				int kth = tree.get_max_prefix_lower(-query).first; // 1-indexation
				tree.increase_value(kth, -1);
			}
		}

		if (tree.get_prefix_sum(n) == 0) {
			cout << 0;
		}
		else {
			cout << tree.get_max_prefix_lower(1).first; // 1-indexation
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