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

size_t rz() {
	size_t v;
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
		++index;
		ll delta = value - values[index];
		values[index] = value;

		update_tree_index(index, delta);
	}

	pair<size_t, ll> get_prefix(ll value) {
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
};

/*
tag bruteforce
tag cases
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		size_t n = rz();
		vi inp = rvi(n);

		sort(inp.begin(), inp.end());

		/*
		a, b + c = 4a, d = 3a
		*/

		auto check = [&](vi& ans) {
			sort(ans.begin(), ans.end());

			int a = ans[0];
			int bc = ans[1] + ans[2];
			int d = ans[3];

			if (a * 4 != bc) return false;
			if (a * 3 != d) return false;

			size_t ind = 0;
			for (int v : ans) {
				if (ind < n && v == inp[ind]) ++ind;
			}

			return ind == n;
		};

		auto gen = [&](int a) -> vi {
			return { a, 2 * a, 2 * a, 3 * a };
		};

		auto get_answer = [&]() -> pair<vi, bool> {
			if (0 == n) {
				return { { 1, 2, 2, 3 }, true };
			} else if (1 == n) {
				int a = inp[0];
				return { gen(a), true };
			}
			else if (4 == n) {
				return { inp, check(inp) };
			}
			else if (2 == n) {
				// a, (b, c, d)
				{
					int a = inp[0];
					int v = inp[1];

					vi ans = gen(a);

					if (v <= 2 * a) {
						ans[1] = v;
						ans[2] = 4 * a - v;
					}
					else if (v == 3 * a) {
						ans[3] = v;
					}
					else {
						ans[2] = v;
						ans[1] = 4 * a - v;
					}

					if (check(ans)) {
						return { ans, true };
					}
				}

				// d, (b, c)
				{
					int d = inp[1];
					int a = (0 == d % 3 ? d / 3 : -1);
					
					vi ans = gen(a);
					if (check(ans)) {
						return { ans, true };
					}
				}

				// (b, c)
				{
					int b = inp[0], c = inp[1];
					int s = b + c;
					int a = (0 == s % 4 ? s / 4 : -1);

					vi ans = gen(a);
					if (check(ans)) {
						return { ans, true };
					}
				}

				return { vi(), false };
			}
			else {
				// a, (bcd)
				{
					int a = inp[0];
					int x = inp[1];

					vi ans = gen(a);

					ans[1] = x;
					ans[2] = 4 * a - x;

					if (check(ans)) {
						return { ans, true };
					}
				}

				// b, c, d
				{
					int d = inp[2];
					int x = inp[0], y = inp[1];

					int a = (0 == d % 3 ? d / 3 : -1);

					vi ans = gen(a);

					ans[1] = x;
					ans[2] = y;

					if (check(ans)) {
						return { ans, true };
					}
				}

				return { vi(), false };
			}
		};

		pair<vi, bool> answer = get_answer();

		if (yn(answer.second)) {
			size_t ind = 0;
			for (int v : answer.first) {
				if (ind < n && v == inp[ind]) ++ind;
				else {
					cout << v << ENDL;
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