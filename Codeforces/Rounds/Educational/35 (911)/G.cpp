#define STRESS_
#ifdef STRESS
#include "Base.h"
#else
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

void read_graph(int n, int edges, graph_t & graph, bool oriented = false) {
	graph.assign(n, vi());
	for (int e = 0; e < edges; ++e) {
		int from = read_size() - 1;
		int to = read_size() - 1;
		graph[from].push_back(to);
		if (!oriented) graph[to].push_back(from);
	}
}

void read_tree(int n, graph_t & graph) {
	read_graph(n, n - 1, graph);
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

void update_max(ll & cur_value, ll new_value) {
	cur_value = max(cur_value, new_value);
}

void update_min(ll & cur_value, ll new_value) {
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

#define RUN

void init() {

}

int n;
vi a;

int q;
vvi queries;

void read_input() {
	n = read_size();
	read_vector(a, n);
	add_to_each(a, -1);

	q = read_size();
	queries.assign(q, vi());
	for (int i = 0; i < q; ++i) {
		read_vector(queries[i], 4);
		add_to_each(queries[i], -1);
	}
}

/*
array
segment query
mass update
sqrt decomposition
linked list
*/

// =============================================

typedef vi ans_t;

// =============================================

ans_t get_answer() {
	int bs = 700;
	int bc = (n - 1) / bs + 1;

	const int maxC = 100;

	vvi heads(bc, vi(maxC, -1));
	vvi lasts(bc, vi(maxC, -1));
	vvi nexts(bc, vi(maxC + maxC));

	auto icb = [&](int b) {
		for (int c = 0; c < maxC; ++c) {
			nexts[b][heads[b][c]] = c;
			nexts[b][c] = -1;
			lasts[b][c] = c;
		}
	};

	for (int b = 0; b < bc; ++b) {
		for (int c = 0; c < maxC; ++c) {
			heads[b][c] = c + maxC;
		}

		icb(b);
	}

	vi b_st(bc + 1, 0);
	for (int b = 1; b <= bc; ++b) {
		b_st[b] = b_st[b - 1] + bs;
	}

	b_st[bc] = n;

	vi tg(maxC, -1);

	auto pb = [&](int b) {
		for (int c = 0; c < maxC; ++c) {
			int h = heads[b][c];
			for (int v = nexts[b][h]; v != -1; v = nexts[b][v]) {
				tg[v] = c;
			}
		}

		for (int i = b_st[b]; i < b_st[b + 1]; ++i) {
			a[i] = tg[a[i]];
		}

		icb(b);
	};

	for (auto & query : queries) {
		const int left = query[0], right = query[1];
		const int fc = query[2], tc = query[3];

		if (fc == tc) continue;

		int lb = left / bs, rb = right / bs;

		if (lb == rb) {
			pb(lb);
			for (int i = left; i <= right; ++i) {
				if (fc == a[i]) a[i] = tc;
			}
		}
		else {
			pb(lb);
			for (int i = left; i < b_st[lb + 1]; ++i) {
				if (fc == a[i]) a[i] = tc;
			}

			pb(rb);
			for (int i = b_st[rb]; i <= right; ++i) {
				if (fc == a[i]) a[i] = tc;
			}

			for (int b = lb + 1; b < rb; ++b) {
				int fh = heads[b][fc];
				int ff = nexts[b][fh];
				int fl = lasts[b][fc];

				if (-1 != ff) {
					int th = heads[b][tc];
					int tl = lasts[b][tc];

					nexts[b][fh] = -1;
					lasts[b][fc] = fh;

					nexts[b][tl] = ff;
					lasts[b][tc] = fl;
				}
			}
		}
	}

	for (int b = 0; b < bc; ++b) {
		pb(b);
	}

	return a;
}

void print_answer(ans_t answer) {
	add_to_each(answer, 1);
	print_vector(answer);
}

void solve_test() {
	read_input();

	ans_t answer = get_answer();

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