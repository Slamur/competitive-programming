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
tag brackets
tag set
*/

vi get_answer(int n, vi& a) {
	vector<size_t> lefts(n, a.size());
	vector<size_t> rights(n, a.size());

	for (size_t i = 0; i < a.size(); ++i) {
		int v = a[i];
		if (a.size() == lefts[v]) lefts[v] = i;
		else rights[v] = i;
	}

	vi ans(n + n, 0);

	bool can = true;

	if (1 == n % 2) {
		can = false;
	}
	else {
		set<int> open, closed;

		for (int i = 0; i < n + n; ++i) {
			if (0 != ans[i]) continue;

			int v = a[i];

			if (open.size() * 2 < n) {
				ans[lefts[v]] = 1;
				ans[rights[v]] = 1;
				open.insert(lefts[v]);
			}
			else {
				ans[lefts[v]] = -1;
				ans[rights[v]] = -1;
			}
		}

		int balance = 0;
		for (size_t i = 0; i < a.size(); ++i) {
			balance += ans[i];

			if (lefts[a[i]] == i) {
				if (ans[i] < 0) {
					closed.insert(lefts[a[i]]);
				}
			}

			if (balance < 0) {
				if (closed.empty() || open.empty()) {
					can = false;
				}
				else {
					int smallest_closed_left = *(closed.begin());
					closed.erase(smallest_closed_left);

					int largest_open_left = *(open.rbegin());
					open.erase(largest_open_left);

					int c = a[smallest_closed_left];
					int o = a[largest_open_left];

					ans[lefts[c]] = 1;
					ans[rights[c]] = 1;

					ans[lefts[o]] = -1;
					ans[rights[o]] = -1;

					if (rights[c] >= i) open.insert(lefts[c]);
					if (lefts[o] <= i) closed.insert(lefts[o]);

					balance += 2;
				}
			}

			if (rights[a[i]] == i) {
				if (ans[i] > 0) {
					open.erase(lefts[a[i]]);
				}
			}
		}

		if (balance != 0) can = false;

		balance = 0;
		for (int i = 0; i < n + n; ++i) {
			balance += ans[i];
			if (balance < 0) can = false;
		}

		if (balance != 0) can = false;
	}

	if (!can) {
		return { 1 };
	}
	else {
		return ans;
	}
}

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {

	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}