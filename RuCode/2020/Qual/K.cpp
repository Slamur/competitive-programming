#define STRESS
#ifdef _STRESS
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

typedef vvii ans_t;

// =============================================

#define RUN

void init() {

}

ans_t get_answer(int w, int h, ii k1, ii s1, ii k2, ii s2) {
	typedef pair<ii, ii> state;

	map<state, int> distances;
	map<state, state> parents;
	queue<state> q;

	state none({ -1, -1 }, { -1, -1 });

	state start(s1, s2);
	distances[start] = 0;
	parents[start] = none;
	q.push(start);

	vi signs = { -1, 1 };

	auto go = [&](int x1, int y1, int x2, int y2, state from) {
		if (!check_cell(x1, w, y1, h)) return;
		if (!check_cell(x2, w, y2, h)) return;

		state to({ x1, y1 }, { x2, y2 });
		if (distances.count(to)) return;

		distances[to] = distances[from] + 1;
		parents[to] = from;
		q.push(to);
	};

	while (q.size()) {
		state from = q.front();
		q.pop();

		int x1 = from.first.first, y1 = from.first.second;
		int x2 = from.second.first, y2 = from.second.second;

		for (int fx : signs) {
			for (int fy : signs) {
				for (int sx : signs) {
					for (int sy : signs) {
						go(x1 + fx * k1.first, y1 + fy * k1.second,
							x2 + sx * k2.first, y2 + sy * k2.second,
							from
							);

						go(x1 + fx * k1.second, y1 + fy * k1.first,
							x2 + sx * k2.first, y2 + sy * k2.second,
							from
						);

						go(x1 + fx * k1.first, y1 + fy * k1.second,
							x2 + sx * k2.second, y2 + sy * k2.first,
							from
						);

						go(x1 + fx * k1.second, y1 + fy * k1.first,
							x2 + sx * k2.second, y2 + sy * k2.first,
							from
						);
					}
				}
			}
		}
	}

	int ans_distance = 1e9;
	state ans_end = none;

	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			ii end = { x, y };
			state end_state(end, end);
			
			if (distances.count(end_state)) {
				int distance = distances[end_state];
				if (ans_distance > distance) {
					ans_distance = distance;
					ans_end = end_state;
				}
			}
		}
	}

	vvii answer;
	for (state cur = ans_end; cur != none; cur = parents[cur]) {
		answer.push_back({ cur.first, cur.second });
	}

	reverse(answer.begin(), answer.end());

	return answer;
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
		int w = read_size();
		int h = read_size();
		ii k1 = read_ii();
		ii k2 = read_ii();
		ii s1 = read_ii();
		ii s2 = read_ii();
		
		s1.first--;
		s1.second--;

		s2.first--;
		s2.second--;

		ans_t answer = get_answer(w, h, k1, s1, k2, s2);

		//cout << answer << ENDL;

		//print(answer);

		cout << (int)answer.size() - 1 << ENDL;
		for (auto & row : answer) {
			add_to_each(row, 1);
			print_pairs(row, SPACE);
		}
	}
#else
	set_print_file("tests.txt");
	stress();
	close_print_file();
#endif
	return 0;
}