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
tag lexicographic
tag digits dp
tag bruteforce
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = ri();

		vector<string> b(n);
		for (int i = 0; i < n; ++i) {
			cin >> b[i];
		}

		vector<string> a(n + 1);
		a[0] = "0";
		for (int i = 1; i <= n; ++i) {
			a[i] = b[i - 1];
		}

		int ml = 8;

		for (string& s : a) {
			reverse(s.begin(), s.end());
			while (s.size() < ml) {
				s.push_back('0');
			}
			reverse(s.begin(), s.end());
		}

		bool correct = true;

		const char ANY = '?';

		vi can(ml + 1);
		for (int it = 1; it <= n; ++it) {
			can.assign(ml + 1, false);

			string& prev = a[it - 1];
			string& cur = a[it];

			for (int i = ml - 1; i >= 0; --i) {
				char d = (ANY == cur[i] ? '9' : cur[i]);

				if (prev[i] > d) {
					can[i] = false;
				}
				else if (prev[i] == d) {
					can[i] = can[i + 1];
				}
				else {
					can[i] = true;
				}
			}

			bool equal = true;
			bool first = true;
			for (int i = 0; i < ml; ++i) {
				if (ANY == cur[i]) {
					if (!equal) cur[i] = '0';
					else cur[i] = prev[i] + (can[i + 1] ? 0 : 1);

					if (first && '0' == cur[i]) cur[i]++;
					if ('9' < cur[i]) {
						correct = false;
						break;
					}
				}

				first &= ('0' == cur[i]);

				if (equal && prev[i] > cur[i]) {
					correct = false;
					break;
				}

				equal &= prev[i] == cur[i];
			}

			correct &= !equal;

			if (!correct) break;			
		}
		
		if (yn(correct)) {
			for (string& s : a) {
				reverse(s.begin(), s.end());
				while (s.size() > 0 && '0' == s.back()) s.pop_back();
				reverse(s.begin(), s.end());

				if (s.size() > 0) cout << s << ENDL;
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