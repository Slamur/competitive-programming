#define _STRESS
#ifdef STRESS
#include "Base.h"
#else
#pragma comment(linker, "/STACK:66777216")

#include <iostream>
#include <vector>
#include <cmath>
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

const char SPACE = ' ', ENDL = '\n';

const int BASE = 1000 * 1000 * 1000 + 7;
const int MODULO = BASE; // 1000 * 1000 * 1000 + 31; //998244353
#endif

template <class T>
T read() {
	T value;
	cin >> value;
	return value;
}

int read_int() {
	return read<int>();
}

size_t read_size() {
	return read<size_t>();
}

ll read_ll() {
	return read<ll>();
}

ii read_ii() {
	int x = read_int();
	int y = read_int();
	return ii(x, y);
}

string read_string() {
	return read<string>();
}

template <class T>
void read_vector(vector<T> & a, size_t size) {
	a.resize(size);
	for (T & value : a) cin >> value;
}

template <class T1, class T2>
void read_pairs(vector<pair<T1, T2>> & a, size_t size) {
	a.resize(size);
	for (auto & value : a) cin >> value.first >> value.second;
}

void add_to_each(vi & a, int delta) {
	for (int & value : a) value += delta;
}

void add_to_each(vii & a, int delta) {
	for (ii & value : a) {
		value.first += delta;
		value.second += delta;
	}
}

template <class T>
void print(vector<T> & a, char sep = SPACE) {
	for (T & value : a) cout << value << sep;
	cout << ENDL;
}

void print_pairs(vii & a, char sep = ENDL) {
	for (ii & value : a) cout << value.first << " " << value.second << sep;
	if (sep != ENDL) cout << ENDL;
}

int get_bit(ll mask, int bit) {
	return (int)((mask >> bit) & 1);
}

ll set_bit(ll mask, int bit) {
	return mask | (1LL << bit);
}

ll clear_bit(ll mask, int bit) {
	return mask & (~(1LL << bit));
}

vi reverse(vi & a) {
	reverse(a.begin(), a.end());
	return a;
}

typedef ll mod_t;

void update_max(int & cur_value, int new_value) {
	cur_value = max(cur_value, new_value);
}

void update_min(int & cur_value, int new_value) {
	cur_value = min(cur_value, new_value);
}

ll gcd(ll a, ll b) {
	return (a == 0 ? b : gcd(b % a, a));
}

ll lcm(ll a, ll b) {
	return (a * b == 0 ? 0 : a / gcd(a, b) * b);
}

bool check_index(int index, int size) {
	return 0 <= index && index < size;
}

bool check_cell(int x, int xSize, int y, int ySize) {
	return check_index(x, xSize) && check_index(y, ySize);
}

// =============================================

typedef pair<sll, sll> ans_t;

// =============================================

#define RUN

void init() {

}

vector<vector<vector<ans_t>>> dp;

vector<vector<sll>> p;

ans_t f(int cur, int fm, int sm) {
	if (dp[cur][fm][sm].first != -1) {
		return dp[cur][fm][sm];
	}

	int index = cur / 2;
	int team = cur % 2;

	if (p[0].size() == index) {
		int fc = 0, sc = 0;
		for (int i = 0; i < p[0].size(); ++i) {
			if (get_bit(fm, i)) ++fc;
		}

		for (int i = 0; i < p[1].size(); ++i) {
			if (get_bit(sm, i)) ++sc;
		}

		double wpr = (fc > sc ? 100 : 0);
		double dpr = (fc == sc ? 100 : 0);

		return (dp[cur][fm][sm] = make_pair(wpr, dpr));
	}

	ans_t best_pr(-1, -1);

	sll pr = get_bit(fm, index) ? p[team][index] : 0;
	sll qr = 100 - pr;
	ans_t missed_pr = f(cur + 1, sm, fm);

	sll total_pr = 1;
	for (int i = 2 * p[0].size(); i >= cur; --i) {
		total_pr *= 100;
	}

	for (int j = 0; j < p[1 - team].size(); ++j) {
		if (!get_bit(sm, j)) continue;

		ans_t killed_pr = f(cur + 1, sm ^ (1 << j), fm);

		sll dpr = pr * killed_pr.second + qr * missed_pr.second;
		sll lpr = pr * killed_pr.first + qr * missed_pr.first;
		sll wpr = total_pr - dpr - lpr;

		ans_t cur_pr(wpr, dpr);
		if (best_pr < cur_pr) {
			best_pr = cur_pr;
		}
	}

	return dp[cur][fm][sm] = best_pr;
}

ans_t get_answer(int n) {
	int mask_limit = (1 << n);

	dp.assign(
		n + n + 1, vector<vector<ans_t>>(
			mask_limit, vector<ans_t>(
				mask_limit, { -1, -1 }
				)
			)
	);

	return f(0, mask_limit - 1, mask_limit - 1);
}

int main() {
#ifdef RUN
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	//#ifndef ONLINE_JUDGE
	//	freopen("input.txt", "r", stdin);
	//	freopen("output.txt", "w", stdout);
	//#endif

	init();

	int tests = 1;// read_size();
	for (int test = 1; test <= tests; ++test) {
		int n = read_size();

		p.assign(2, vector<sll>(n, 0));

		for (int team = 0; team < 2; ++team) {
			for (int i = 0; i < n; ++i) {
				string s = read_string();
				p[team][i] = (s[0] - '0') * 100 + (s[2] - '0') * 10 + (s[3] - '0') * 1;
			}
		}

		ans_t answer = get_answer(n);

		auto to_prob = [&](sll value) {
			for (int i = 0; i < 2 * n - 1; ++i) value /= 100;
			value /= 10;

			if (value % 10 >= 5) value += 10;
			value /= 10;

			string res = "";
			res += (value / 100 + '0');
			res += ".";
			res += (value / 10 % 10 + '0');
			res += (value % 10 + '0');

			return res;
		};

		cout << setprecision(2) << fixed;
		cout << to_prob(answer.first) << " " << to_prob(answer.second) << ENDL;
		//cout << answer << ENDL;
		//print(answer);
		//for (vi & row : answer) {
		//	add_to_each(row, 1);
		//	print(row);
		//}
	}
#else
	set_print_file("tests.txt");
	stress();
	close_print_file();
#endif
	return 0;
}