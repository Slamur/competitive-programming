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
tag multiset
tag maximum
tag average / mean
tag queries
tag prefix sums
tag binary search
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		/*
		max(s) - mean(s) -> max
		max(s) = v (a[k])

		s[i] = [a[1..i] + v]
		mean(i) = (p[i] + v) / (i + 1)

		mean(i) -> min
		mean(i - 1) >= mean(i) <= mean(i + 1)

		(p[i - 1] + v) / i >= (p[i - 1] + v + a[i]) / (i + 1)
		(p[i - 1] + v) * i + (p[i - 1] + v) >= (p[i - 1] + v) * i + a[i] * i
		p[i - 1] + v >= a[i] * i
		v >= a[i] * i - p[i - 1]
		v <= a[i + 1] * (i + 1) - p[i]

		s[i] = a[i] * i - p[i - 1]
		s[i] <= v <= s[i + 1]
		
		P.S.
		s[i - 1] < s[i]

		a[i - 1] * (i - 1) - p[i - 2] < a[i] * i - p[i - 1]
		a[i - 1] * i - (a[i - 1] + p[i - 2]) < a[i] * i - p[i - 1]
		a[i - 1] * i - p[i - 1] < a[i] * i - p[i - 1]
		a[i - 1] <= a[i] - by the statement
		*/

		int q = ri();
		vll p(1, 0);
		vll s(1, -1);

		double ans = -1;


		for (int it = 0; it < q; ++it) {
			int type = ri();

			if (1 == type) {
				ll x = rll();

				size_t size = p.size();
				ll sum = p.back();

				p.push_back(sum + x);
				s.push_back(x * size - sum);

				auto it = upper_bound(s.begin(), s.end(), x); // we found s[i + 1]
				int index = distance(s.begin(), it) - 1;

				double mean = (double)(p[index] + x) / (index + 1.0);
				double res = x - mean;

				ans = max(ans, res);
			}
			else {
				cout << ans << ENDL;
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