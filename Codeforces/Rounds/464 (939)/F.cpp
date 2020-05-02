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

template <class V>
class MinimumQueue {
	typedef pair<V, int> T;
private:
	deque<T> q;
public:
	MinimumQueue()
	{ }

	void push(V value) {
		int cnt = 1;
		while (q.size() > 0) {
			T last = q.back();
			if (last.first > value) {
				cnt += last.second;
				q.pop_back();
			}
			else {
				break;
			}
		}

		q.push_back({ value, cnt });
	}

	V min(V inf) {
		if (q.empty()) return inf;

		return q.front().first;
	}

	void poll() {
		if (q.empty()) return;

		auto& first = q.front();
		--first.second;
		if (0 == first.second) {
			q.pop_front();
		}
	}
};

/*
tag dp
tag knapsack
tag 2 layer
tag window
tag segment minimum
tag minimum queue
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int total = ri();
		int n = ri();

		vi lefts(n);
		vi rights(n);

		for (int i = 0; i < n; ++i) {
			cin >> lefts[i] >> rights[i];
		}

		if (rights.back() < total + total) {
			++n;
			lefts.push_back(total + total);
			rights.push_back(total + total);
		}

		const int inf = (int)1e9;

		const int f = 0, s = 1;
		const int st = 0, fn = 1;

		vector<vvi> dp(2, vvi(2, vi(total + 1, inf)));

		dp[fn][f][0] = 0;

		for (int seg_index = 0; seg_index < n; ++seg_index) {
			int pd = lefts[seg_index] - (0 == seg_index ? 0 : rights[seg_index - 1]);

			for (int t = 0; t <= total; ++t) {
				dp[st][f][t] = inf;
				if (t >= pd) {
					dp[st][f][t] = min(dp[st][f][t], dp[fn][f][t - pd]);
				}

				dp[st][s][t] = dp[fn][s][t];

				dp[st][f][t] = min(dp[st][f][t], dp[st][s][t] + 1);
				dp[st][s][t] = min(dp[st][s][t], dp[st][f][t] + 1);
			}

			int ld = rights[seg_index] - lefts[seg_index];

			MinimumQueue<int> qf, qs;

			for (int d = 0; d <= ld; ++d) {
				qf.push(inf);
				qs.push(inf);
			}

			for (int t = 0; t <= total; ++t) {
				dp[fn][f][t] = inf;
				dp[fn][s][t] = inf;

				// 0 changes
				if (t >= ld) {
					dp[fn][f][t] = min(dp[fn][f][t], dp[st][f][t - ld]);
				}				

				dp[fn][s][t] = min(dp[fn][s][t], dp[st][s][t]);

				// 1 change
				qf.push(dp[st][f][t]);
				qs.push(dp[st][s][t]);

				qf.poll();
				qs.poll();

				dp[fn][f][t] = min(dp[fn][f][t], qs.min(inf) + 1);
				dp[fn][s][t] = min(dp[fn][s][t], qf.min(inf) + 1);
			}
		}

		int answer = min(dp[fn][f][total], dp[fn][s][total]);

		if (yn(answer < inf, "Full", "Hungry")) {
			cout << answer << ENDL;
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