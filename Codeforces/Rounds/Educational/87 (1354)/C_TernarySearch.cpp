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

/*
tag multitest
tag geometry
tag perfect polygon
tag ternary search
tag rotation
*/

void solve_test() {
	int tests = ri();
	for (int test = 1; test <= tests; ++test) {
		int n = ri();
		double alpha = M_PI / n;

		/*
		a / 2 / R = sin(alpha / 2)
		R = a / 2 * sin(alpha / 2)
		*/
		double radius = 0.5 / sin(alpha / 2);

		double x = radius, y = 0;

		auto f = [&](double rotateAngle) {
			int size = n + n;

			vector<double> xs(size, 0);
			vector<double> ys(size, 0);

			for (int i = 0; i < size; ++i) {
				double angle = i * alpha + rotateAngle;

				xs[i] = x * cos(angle) + y * sin(angle);
				ys[i] = x * (-sin(angle)) + y * cos(angle);
			}

			double minY = 1e18, maxY = -1e18;
			double minX = 1e18, maxX = -1e18;

			for (double x : xs) {
				minX = min(minX, x);
				maxX = max(maxX, x);
			}

			for (double y : ys) {
				minY = min(minY, y);
				maxY = max(maxY, y);
			}

			return max(maxX - minX, maxY - minY);
		};

		double left = 0, right = alpha;
		for (int it = 0; it < 100; ++it) {
			double m1 = left + (right - left) / 3;
			double m2 = right - (right - left) / 3;

			double s1 = f(m1);
			double s2 = f(m2);

			if (s1 > s2) left = m1;
			else right = m2;
		}

		double ans = f(left);

		cout << setprecision(10) << fixed << ans << ENDL;
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}