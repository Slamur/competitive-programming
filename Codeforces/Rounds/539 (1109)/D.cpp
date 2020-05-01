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

inline mod_t add(mod_t a, mod_t b) {
	return (a + b) % MODULO;
}

inline void add_to(mod_t& a, mod_t b) {
	a += b;
	if (a >= MODULO) a -= MODULO;
}

inline mod_t subtract(mod_t a, mod_t b) {
	return add(a, MODULO - b);
}

inline void subtract_from(mod_t& a, mod_t b) {
	a -= b;
	if (a < 0) a += MODULO;
}

inline mod_t multiply(mod_t a, mod_t b) {
	return ((a * b) % MODULO);
}

mod_t binpow(int base, ll power) {
	if (power == 0) return 1;

	ll result = binpow(base, power >> 1);
	result = multiply(result, result);

	if (power & 1) {
		result = multiply(result, base);
	}

	return result;
};

mod_t inverse(int value) {
	return binpow(value, MODULO - 2);
}

/*
tag combinatorics
tag tree
tag labeled tree
tag caylee formula (https://en.wikipedia.org/wiki/Cayley's_formula)
tag with tutorial
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = ri();
		int m = ri();

		// a, b not needed
		ri();
		ri();

		const int ml = (int) 1e6;

		vll facts(ml + 1, 1);
		for (int i = 1; i <= ml; ++i) {
			facts[i] = multiply(facts[i - 1], i);
		}

		vll ifacts(ml + 1, 1);
		ifacts[ml] = inverse(facts[ml]);

		for (int i = ml; i > 0; --i) {
			ifacts[i - 1] = multiply(ifacts[i], i);
		}
		
		auto a = [&](int total, int need) {
			return multiply(facts[total], ifacts[total - need]);
		};

		auto c = [&](int total, int need) {
			return multiply(a(total, need), ifacts[need]);
		};

		vll nps(ml + 1, 0);
		nps[0] = 1;
		for (int i = 1; i <= ml; ++i) {
			nps[i] = multiply(nps[i - 1], n);
		}

		vll mps(ml + 1, 0);
		mps[0] = 1;
		for (int i = 1; i <= ml; ++i) {
			mps[i] = multiply(mps[i - 1], m);
		}

		auto f = [&](int roots) -> mod_t {
			if (roots == n) return 1;
			return multiply(roots, nps[n - roots - 1]);
		};

		mod_t ans = 0;

		for (int e = 1; e <= min(m, n - 1); ++e) {
			mod_t weights_on_path = c(m - 1, e - 1); // balls and barriers
			mod_t weights_other = mps[n - 1 - e];

			mod_t weights = multiply(weights_on_path, weights_other);

			mod_t vertexes_on_path = a(n - 2, e - 1);
			mod_t forests = f(e + 1);

			mod_t vertexes = multiply(vertexes_on_path, forests);

			mod_t trees = multiply(weights, vertexes);
			add_to(ans, trees);
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