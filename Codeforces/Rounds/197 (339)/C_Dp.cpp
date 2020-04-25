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

// taken from https://codeforces.com/blog/entry/76149?#comment-606512

//template<class... Args>
//auto create(size_t n, Args&&... args) {
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
tag dp
tag states 3
tag path recovery
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		string s;
		cin >> s;

		int m = ri();

		s.insert(s.begin(), '0');

		int k = s.size();

		vi has(k, false);
		for (int w = 0; w < k; ++w) {
			has[w] = s[w] - '0';
		}

		const int NONE = -1, START = -2;

		vector<vvi> dp(m + 1, vvi(k, vi(k, NONE)));
		dp[0][0][0] = START;

		vii dirs = { { 0, 1 }, { k - 1, -1 } };

		for (int i = 0; i < m; ++i) {
			for (int d = 0; d < k; ++d) {
				for (ii & dir : dirs) {
					int prev = NONE;
					for (int w = dir.first; 0 <= w && w < k; w += dir.second) {
						if (has[w] && d < w && NONE != prev) {
							dp[i + 1][w - d][w] = prev;
						}

						if (NONE != dp[i][d][w]) {
							prev = w;
						}
					}
				}
			}
		}

		ii last(NONE, NONE);
		for (int d = 0; d < k; ++d) {
			for (int w = 0; w < k; ++w) {
				if (NONE != dp[m][d][w]) {
					last.first = d;
					last.second = w;
				}
			}
		}

		if (yn(NONE != last.first)) {
			vi path;
			for (int i = m, d = last.first, w = last.second; i > 0; --i) {
				path.push_back(w);
				
				int next_w = dp[i][d][w];

				d = w - d;
				w = next_w;
			}

			reverse(path.begin(), path.end());

			for (int w : path) {
				cout << w << SPACE;
			}

			cout << ENDL;
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