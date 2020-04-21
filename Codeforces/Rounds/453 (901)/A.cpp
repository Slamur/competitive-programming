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

typedef vvi ans_t;

// =============================================

#define RUN

void init() {

}

#ifndef STRESS
struct Input {
	int n;
	vi a;

	Input(int n, vi a) : n(n), a(a) { }
};
#endif

Input read_input() {
	int n = read_size();

	vi a;
	read_vector(a, n + 1);

	return Input(n, a);
}

/*
#tree
#hash
#isomorphism
*/

ans_t get_answer(Input & input) {
	int h = input.n;
	vi & a = input.a;

	int n = 0;
	for (int v : a) n += v;

	vvi rows(h + 1);
	for (int i = 0, v = 0; i <= h; ++i) {
		for (int j = 0; j < a[i]; ++j, ++v) {
			rows[i].push_back(v);
		}
	}

	bool consecutive_twos = false;
	for (int i = 1; i <= h; ++i) {
		consecutive_twos |= (rows[i].size() > 1 && rows[i - 1].size() > 1);
	}

	if (!consecutive_twos) {
		return vvi(0);
		// perfect
	}

	vi p1(n, -1);
	vi p2(n, -1);

	for (int i = 1; i <= h; ++i) {
		int pf = rows[i - 1].front(), pl = rows[i - 1].back();
		for (int v : rows[i]) {
			p1[v] = pf;
			p2[v] = pl;
		}

		p2[rows[i].front()] = pf;
	}

	return { p1, p2 };
}

void print_answer(ans_t answer) {
	if (answer.empty()) {
		cout << "perfect" << endl;
	}
	else {
		cout << "ambiguous" << endl;
		for (auto & row : answer) {
			add_to_each(row, 1);
			print_vector(row);
		}
	}
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