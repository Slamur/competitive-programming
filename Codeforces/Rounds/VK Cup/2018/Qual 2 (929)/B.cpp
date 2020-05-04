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
tag string
tag priority queue
tag counting
*/

void solve_test() {
	int tests = 1; // ri();
	while (tests-- > 0) {
		int n = ri();
		int k = ri();
		vector<string> rows(n);
		for (int i = 0; i < n; ++i) {
			rows[i] = "-" + rs() + "-";
		}

		int ans = 0;

		vvii frees(3, vii());

		for (int i = 0; i < n; ++i) {
			string& row = rows[i];
			for (int j = 0; j < row.size(); ++j) {
				switch (row[j]) {
				case 'S':
					if ('P' == row[j - 1] || 'S' == row[j - 1]) ++ans;
					if ('P' == row[j + 1] || 'S' == row[j + 1]) ++ans;
					break;
				case '.':
					int cnt = 0;
					if ('S' == row[j - 1]) ++cnt;
					if ('S' == row[j + 1]) ++cnt;

					frees[cnt].push_back({ i, j });
					break;
				}
			}
		}

		for (int cnt = 0; cnt < 3; ++cnt) {
			while (frees[cnt].size() > 0 && k > 0) {
				ii& pos = frees[cnt].back();
				frees[cnt].pop_back();

				rows[pos.first][pos.second] = 'x';
				ans += cnt;
				--k;
			}
		}

		cout << ans << ENDL;
		for (string& row : rows) {
			cout << row.substr(1, row.size() - 2) << ENDL;
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