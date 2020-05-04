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
tag combinatorics
tag binomial coefficients
tag counting
tag inclusion-exclusion
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = 3;
		vi sizes = rvi(n);

		vvi ids(n, vi());
		for (int i = 0; i < n; ++i) {
			ids[i] = rvi(sizes[i]);
		}

		const int maxId = (int)1e5;
		vvi counts(n, vi(maxId + maxId + 1, 0));

		for (int i = 0; i < n; ++i) {
			for (int id : ids[i]) {
				counts[i][id]++;
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int id = 1; id < counts[i].size(); ++id) {
				counts[i][id] += counts[i][id - 1];
			}
		}

		auto c = [&](int n, int k) {
			ll num = 1, denum = 1;
			for (ll i = 0; i < k; ++i) {
				num *= n - i;
				denum *= (i + 1);
			}

			return num / denum;
		};

		vi needs = { 1, 2, 3 };

		ll ans = 0;

		for (int start = 1; start <= maxId; ++start) {
			int end = start * 2;

			ll res_cur = 1;
			ll res_next = 1;
			for (int i = 0; i < n; ++i) {
				int need = needs[i];
				int has_cur = counts[i][end] - counts[i][start - 1];
				int has_next = counts[i][end] - counts[i][start];

				res_cur *= c(has_cur, need);
				res_next *= c(has_next, need);
			}

			ans += res_cur - res_next;
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