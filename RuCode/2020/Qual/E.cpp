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

ll gcd(ll a, ll b) {
	return (a == 0 ? b : gcd(b % a, a));
}

ll lcm(ll a, ll b) {
	return (a * b == 0 ? 0 : a / gcd(a, b) * b);
}

class fraction {
private:
	void normalize() {
		if (d == 0) return;

		ll g = gcd(std::abs(n), std::abs(d));
		n /= g;
		d /= g;

		if (d < 0) {
			n *= -1;
			d *= -1;
		}
	}

public:
	ll n, d;

	fraction(int n, int d)
		: n(n)
		, d(d)
	{
		normalize();
	}

	fraction(int n) : fraction(n, 1)
	{ }

	fraction() : fraction(0)
	{ }

	fraction multiply(const ll val) const {
		return fraction(n * val, d);
	}

	fraction inverse() const {
		return fraction(d, n);
	}

	fraction operator+(const fraction & other) const {
		ll res_num = n * other.d + other.n * d;
		ll res_denom = d * other.d;
		return fraction(res_num, res_denom);
	}

	fraction operator-(const fraction & other) const {
		return operator+(other.multiply(-1LL));
	}

	fraction operator*(const fraction & other) const {
		ll res_num = n * other.n;
		ll res_denom = d * other.d;
		return fraction(res_num, res_denom);
	}

	fraction operator/(const fraction & other) const {
		return operator*(other.inverse());
	}

	fraction abs() const {
		return fraction(std::abs(n), d);
	}

	bool is_int() {
		return d != 0 && n % d == 0;
	}

	bool operator<(const fraction & other) const {
		return operator-(other).n < 0;
	}

	bool operator>(const fraction & other) const {
		return other < *this;
	}
};

bool check_index(int index, int size) {
	return 0 <= index && index < size;
}

bool check_cell(int x, int xSize, int y, int ySize) {
	return check_index(x, xSize) && check_index(y, ySize);
}

// =============================================

typedef string ans_t;

// =============================================

#define RUN

void init() {

}

ans_t get_answer(ii & wk, ii & wr, ii & bk) {
	vvi field(8, vi(8, 0));

	const int WK = 1, WR = 2, BK = 3;

	field[wk.first][wk.second] = WK;
	field[wr.first][wr.second] = WR;
	field[bk.first][bk.second] = BK;

	auto is_wk_attacks = [&](int x, int y) {
		for (int dx = -1; dx <= 1; ++dx) {
			for (int dy = -1; dy <= 1; ++dy) {
				if (wk.first + dx == x && wk.second + dy == y) return true;
			}
		}

		return false;
	};

	auto is_wr_attacks = [&](int x, int y) {
		if (wr.first == x && wr.second == y) return false;

		for (int dx = -8; dx <= 8; ++dx) {
			if (wr.first + dx == x && wr.second == y) {
				for (int mx = min(x, wr.first) + 1; mx < max(x, wr.first); ++mx) {
					if (field[mx][y] == WK) return false;
				}

				return true;
			}
		}

		for (int dy = -8; dy <= 8; ++dy) {
			if (wr.second + dy == y && wr.first == x) {
				for (int my = min(y, wr.second) + 1; my < max(y, wr.second); ++my) {
					if (field[x][my] == WK) return false;
				}

				return true;
			}
		}
		
		return false;
	};

	if (is_wk_attacks(bk.first, bk.second)) {
		return "Strange";
	}

	bool is_bk_attacked = is_wr_attacks(bk.first, bk.second);
	
	for (int dx = -1; dx <= 1; ++dx) {
		for (int dy = -1; dy <= 1; ++dy) {
			if (abs(dx) + abs(dy) == 0) continue;

			int x = bk.first + dx, y = bk.second + dy;
			if (!check_cell(x, 8, y, 8)) continue;

			bool is_cell_attacked = is_wr_attacks(x, y) || is_wk_attacks(x, y);
			if (!is_cell_attacked) {
				return (is_bk_attacked ? "Check" : "Normal");
			}
		}
	}

	return (is_bk_attacked ? "Checkmate" : "Stalemate");
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
		
		auto read_chess_pos = []() {
			string pos = read_string();
			return ii(pos[0] - 'a', pos[1] - '1');
		};

		ii wk = read_chess_pos();
		ii wr = read_chess_pos();
		ii bk = read_chess_pos();
			
		ans_t answer = get_answer(wk, wr, bk);
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