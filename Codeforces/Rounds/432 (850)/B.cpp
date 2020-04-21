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
void print(T & a, char sep = ENDL) {
	cout << a << sep;
}

template <class T>
void print_vector(vector<T> & a, char sep = SPACE) {
	for (T & value : a) cout << value << sep;
	if (sep != ENDL) cout << ENDL;
}

template <class T>
void print_matrix(vector<vector<T>> & a, char sep = SPACE) {
	for (vector<T> & row : a) {
		print_vector(row, sep);
	}
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

typedef ll ans_t;

// =============================================

#define RUN

void init() {

}

#ifndef STRESS
struct Input {
	int n;
	ll x, y;
	vi a;

	Input(int n, vi a, ll x, ll y) : n(n), a(a), x(x), y(y) { }
};
#endif

Input read_input() {
	int n = read_size();
	ll x = read_ll();
	ll y = read_ll();

	vi a;
	read_vector(a, n);

	return Input(n, a, x, y);
}

/*
#divisors
#harmonic
#prefix sums
#gcd
*/

ans_t get_answer(Input & input) {
	int n = input.n;
	vi & a = input.a;

	sll x = input.x, y = input.y;

	const int MAX_D = 1e6;
	vll cnt(MAX_D + MAX_D + 1, 0);
	vll cntMult(MAX_D + MAX_D + 1, 0);

	for (int v : a) {
		cnt[v]++;
	}

	for (int d = 1; d < cnt.size(); ++d) {
		cntMult[d] = cnt[d] * d;
		
		cnt[d] += cnt[d - 1];
		cntMult[d] += cntMult[d - 1];
	}

	ans_t answer = std::numeric_limits<ll>::max();

	ll xdy = (x - 1) / y + 1;

	for (int d = 2; d <= MAX_D; ++d) {
		sll cost = 0;
		sll lx = max(0LL, d - xdy);

		for (int m = 0; m < MAX_D; m += d) {
			sll yc = y * ((m + d) * (cnt[m + d] - cnt[m + lx]) - (cntMult[m + d] - cntMult[m + lx]));
			sll xc = x * (cnt[m + lx] - cnt[m]);

			cost += xc + yc;
			if (answer < cost) {
				break;
			}
		}

		if (answer > cost) {
			answer = cost;
		}
	}
	
	return answer;
}

void print_answer(ans_t answer) {
	print(answer);
}

void solve_test() {
	Input input = read_input();

	ans_t answer = get_answer(input);

	print_answer(answer);
}

int main() {
#ifdef RUN
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	#ifndef ONLINE_JUDGE
		freopen("input.txt", "r", stdin);
		freopen("output.txt", "w", stdout);
	#endif

	init();

	int tests =
#ifdef ONLINE_JUDGE
		1;// read_size();
#else
		read_size();
#endif
	for (int test = 1; test <= tests; ++test) {
		solve_test();
	}
#else
	set_print_file("tests.txt");
	stress();
	close_print_file();
#endif
	return 0;
}