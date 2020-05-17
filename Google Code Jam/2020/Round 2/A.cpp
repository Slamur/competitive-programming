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
tag binary search
tag arithmetic progression
*/

typedef pair<ll, pair<ll, ll>> triple;

triple get_fast(ll left, ll right) {
	ll delta = abs(left - right);

	ll leftFirst = 0, rightFirst = (ll)2e9;
	while (rightFirst - leftFirst > 1) {
		ll midFirst = (leftFirst + rightFirst) / 2;

		ll used = midFirst * (midFirst + 1) / 2;
		if (used <= delta) {
			leftFirst = midFirst;
		}
		else {
			rightFirst = midFirst;
		}
	}

	ll result = leftFirst;
	if (left >= right) left -= (result + 1) * result / 2;
	else right -= (result + 1) * result / 2;

	ll next = leftFirst + 1;
	if (right > left) {
		if (right >= next) {
			right -= next;
			++next;
		}
	}
	// left - right - left - right - ....

	ll leftTotal = -1, rightTotal = (ll)2e9;
	while (rightTotal - leftTotal > 1) {
		ll midTotal = (leftTotal + rightTotal) / 2;

		ll rightUsed = midTotal / 2;
		ll leftUsed = midTotal - rightUsed;

		ll leftSum = next * leftUsed + (leftUsed - 1) * leftUsed;
		ll rightSum = next * rightUsed + rightUsed * rightUsed;

		if (left >= leftSum && right >= rightSum) {
			leftTotal = midTotal;
		}
		else {
			rightTotal = midTotal;
		}
	}

	ll totalAfterNext = leftTotal;

	ll rightUsed = totalAfterNext / 2;
	ll leftUsed = totalAfterNext - rightUsed;

	ll leftSum = next * leftUsed + (leftUsed - 1) * leftUsed;
	ll rightSum = next * rightUsed + rightUsed * rightUsed;

	left -= leftSum;
	right -= rightSum;

	ll total = next + totalAfterNext - 1;

	return { total, { left, right } };
}

void solve_test() {
	int tests = ri();
	for (int test = 1; test <= tests; ++test) {
		cout << "Case #" << test << ": ";

		ll left = rll();
		ll right = rll();

		//triple brute = get_brute(left, right);
		triple fast = get_fast(left, right);

		//cout << brute.first << SPACE << brute.second.first << SPACE << brute.second.second << ENDL;
		cout << fast.first << SPACE << fast.second.first << SPACE << fast.second.second << ENDL;
	}
}

int main() {
	int local_tests = init_input();

	for (int local_test = 0; local_test < local_tests; ++local_test) {
		solve_test();
	}

	return 0;
}