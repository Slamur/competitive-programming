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
graph_t graph;

void read_input() {
	n = read_size();
	read_vector(a, n);
	read_tree(n, graph);
}

/*
#graph theory
#tree
#euler
#traverse
*/

// =============================================

typedef vll ans_t;

// =============================================

ans_t answer;

vi sizes;

vi order;
vvi ct;

vi tin, tout;

vi nt;
int dt;

void dfs(int from = 0, int p = -1) {
	int color = a[from];

	order.push_back(from);
	tin[from] = dt++;

	ct[color].push_back(tin[from]);

	sizes[from] = 1;

	for (int to : graph[from]) {
		if (to != p) {
			dfs(to, from);
			sizes[from] += sizes[to];
		}
	}

	order.push_back(from);
	tout[from] = dt++;

	nt[from] = ct[color].size();
	ct[color].push_back(tout[from]);
	
}

int cur;
int col;
vi tree;

void f(int ps, int max_t) {
	ll & ans = answer[col];

	vi sz;

	while (cur < tree.size()) {
		int t = tree[cur];
		if (t >= max_t) break;

		int v = order[t];

		sz.push_back(sizes[v]);

		++cur;

		ll sum = 0;
		for (int to : graph[v]) {
			if (tin[to] < tin[v]) continue;
			f(sizes[to], tout[to]);

			ans += sizes[to] * sum;
			sum += sizes[to];
		}

		ans += sizes[v];

		cur = nt[v] + 1;
	}

	ll sum = 0;
	for (ll size : sz) {
		ans += size * (ps - size);
		ans -= size * sum;
		sum += size;
	}
}

ans_t get_answer() {
	order.clear();
	ct.assign(n + 1, vi(0));
	sizes.assign(n, 0);
	tin.assign(n, -1);
	tout.assign(n, -1);
	nt.assign(n, -1);
	dt = 0;

	dfs();

	answer.assign(n, 0);
	for (int c = 1; c <= n; ++c) {
		cur = 0;
		col = c - 1;
		tree = ct[c];
		f(n, order.size());
	}

	return answer;
}

void print_answer(ans_t answer) {
	print_vector(answer, ENDL);
	cout << ENDL;
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