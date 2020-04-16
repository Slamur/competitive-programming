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
typedef pair<ii, int> iii;
typedef pair<iii, int> iii_indexed;

typedef vector<int> vi;
typedef vector<size_t> vsz;

typedef vector<ll> vll;
typedef vector<vll> vvll;

typedef vector<ii> vii;
typedef vector<vii> vvii;

typedef vector<iii> viii;
typedef vector<iii_indexed> viii_indexed;

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

void read_iii(viii & a, size_t size) {
	a.resize(size);
	for (iii & value : a) cin >> value.first.first >> value.first.second >> value.second;
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
	cout << '\n';
}

template <class T>
vector<int> compress(vector<T> & values) {
	vector<T> sorted = values; // copying
	sort(sorted.begin(), sorted.end());
	sorted.resize(unique(sorted.begin(), sorted.end()) - sorted.begin());

	vector<int> result(values.size());
	for (int i = 0; i < values.size(); ++i) {
		result[i] = lower_bound(sorted.begin(), sorted.end(), values[i]) - sorted.begin();
	}

	return result;
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

string reverse(string s) {
	reverse(s.begin(), s.end());
	return s;
}

vi reverse(vi & a) {
	reverse(a.begin(), a.end());
	return a;
}

vector<int> concat_separated(vi & a, vi & b, int sep = -1) {
	size_t n = a.size(), m = b.size();
	vi s(n + 1 + m);
	for (int i = 0; i < n; ++i) s[i] = a[i];
	s[n] = sep;
	for (int j = 0; j < m; ++j) s[n + 1 + j] = b[j];
	return s;
}

typedef ll mod_t;

inline mod_t add(mod_t a, mod_t b) {
	return (a + b) % MODULO;
}

inline void add_to(mod_t & a, mod_t b) {
	a += b;
	if (a >= MODULO) a -= MODULO;
}

inline mod_t subtract(mod_t a, mod_t b) {
	return add(a, MODULO - b);
}

inline void subtract_from(mod_t & a, mod_t b) {
	a -= b;
	if (a < 0) a += MODULO;
}

inline mod_t multiply(mod_t a, mod_t b) {
	return ((a * b) % MODULO);
}

mod_t binpow(int base, ll power) {
	if (power == 0) return 1;

	ll result = binpow(base, power >> 1);
	result = multiply(result, result);

	if (power & 1) {
		result = multiply(result, base);
	}

	return result;
};

mod_t inverse(int value) {
	return binpow(value, MODULO - 2);
}

ll sum(ll left, ll right) {
	ll sum = left + right;
	ll length = (right - left + 1);
	if (length % 2 == 0) {
		length /= 2;
	}
	else {
		sum /= 2;
	}

	return multiply(sum, length);
}

ll inv6 = inverse(6);

ll squares_sum(ll n) {
	return multiply(inv6, multiply(n, multiply(n + 1, n + n + 1)));
}

ll pow_for(ll base, int power, ll limit) {
	ll result = 1;
	for (int i = 0; i < power; ++i) {
		if (result > limit / base) return limit + 1;

		result *= base;
	}
	return result;
}

void update_max(int & cur_value, int new_value) {
	cur_value = max(cur_value, new_value);
}

void update_min(int & cur_value, int new_value) {
	cur_value = min(cur_value, new_value);
}

void multiply(vvll & left, vvll & right, vvll & res) {
	int columns_count = res[0].size();

	for (int row = 0; row < res.size(); ++row) {
		for (int column = 0; column < columns_count; ++column) {
			res[row][column] = 0;
		}
	}

	for (int row = 0; row < left.size(); ++row) {
		for (int mid = 0; mid < right.size(); ++mid) {
			ll left_val = left[row][mid];

			for (int column = 0; column < columns_count; ++column) {
				add_to(res[row][column], multiply(left_val, right[mid][column]));
			}
		}
	}
}

// =============================================

typedef ll ans_t;

// =============================================

#define RUN

void init() {

}

ans_t get_answer(int n) {
	//vll sizes(n + 5, 0);
	//sizes[1] = 1, sizes[2] = 1;

	//ll sum = sizes[1] + sizes[2];
	//for (int i = 3; i <= n; ++i) {
	//	sizes[i] = sum;
	//	sum += sizes[i];
	//}

	//ll answer = 0;
	//for (int i = 1; i <= n; ++i) {
	//	answer += sizes[i];
	//}

	//return answer;

	return (1LL << (n - 1));
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
		//cout << "Case #" << test << ": ";

		int n = read_size();
			
		ans_t answer = get_answer(n);
		cout << answer << ENDL;
		//print(answer);
	}
#else
	set_print_file("tests.txt");
	stress();
	close_print_file();
#endif
	return 0;
}