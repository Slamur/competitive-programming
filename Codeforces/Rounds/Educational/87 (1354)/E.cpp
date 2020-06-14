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
tag graph
tag bipartite graph
tag dp
tag knapsack
tag answer recovery
*/

void solve_test() {
	int tests = 1;
	for (int test = 1; test <= tests; ++test) {
		int n = ri();
		int m = ri();

		vi cnts = rvi(3);

		graph_t graph;
		read_graph(n, m, graph);

		vi ids(n, -1);
		vi parities(n, -1);

		auto colorize = [&](int start, int id) {
			queue<int> q;
			q.push(start);
			ids[start] = id;
			parities[start] = 0;

			while (q.size()) {
				int from = q.front();
				q.pop();

				for (int to : graph[from]) {
					if (id == ids[to]) {
						if (parities[to] == parities[from]) return false;
					}
					else {
						ids[to] = id;
						parities[to] = parities[from] ^ 1;
						q.push(to);
					}
				}
			}

			return true;
		};

		bool is_bp = true;

		int components_count = 0;
		for (int v = 0; v < n; ++v) {
			if (-1 == ids[v]) {
				is_bp &= colorize(v, components_count);
				++components_count;
			}
		}

		auto calc_colors = [&]() {
			vvi sizes(components_count, vi(2, 0));
			for (int v = 0; v < n; ++v) {
				sizes[ids[v]][parities[v]]++;
			}

			vvi dp(components_count + 1, vi(n + 1, 0));
			dp[0][0] = true;

			for (int id = 0; id < components_count; ++id) {
				for (int cnt = 0; cnt <= n; ++cnt) {
					for (int p = 0; p < 2; ++p) {
						int size = sizes[id][p];
						if (cnt >= size) {
							dp[id + 1][cnt] |= dp[id][cnt - size];
						}
					}
				}
			}

			if (!dp[components_count][cnts[1]]) return vi();

			vi path;

			for (int id = components_count - 1, cnt = cnts[1]; id >= 0; --id) {
				for (int p = 0; p < 2; ++p) {
					int size = sizes[id][p];
					if (cnt >= size && dp[id][cnt - size]) {
						cnt -= size;
						path.push_back(p);
						break;
					}
				}
			}

			reverse(path.begin(), path.end());

			return path;
		};

		vi component_colors = is_bp ? calc_colors() : vi();
		if (yn(is_bp && component_colors.size())) {
			for (int v = 0; v < n; ++v) {
				int id = ids[v], p = parities[v];

				if (p == component_colors[id]) {
					cout << 2;
				}
				else if (cnts[0]) {
					--cnts[0];
					cout << 1;
				}
				else {
					cout << 3;
				}
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