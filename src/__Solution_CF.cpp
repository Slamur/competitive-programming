#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vii = vector<ii>;
using vs = vector<string>;
using vd = vector<double>;
using vb = vector<bool>;

const char SPACE = ' ', ENDL = '\n';

//////////////////////////////////////////////////////////////////

const int MODULO = 1e9 + 7;

void readd(ll& target, ll add) {
	target += add;
	target %= MODULO;
}

ll add(ll target, ll add) {
    ll result = target;
    readd(result, add);
    return result;
}

inline ll negate_mod(ll x) {
    return MODULO - x % MODULO;
}

void resub(ll& target, ll sub) {
    readd(target, negate_mod(sub));
}

ll sub(ll target, ll sub){
	return add(target, negate_mod(sub));
}

void remult(ll& target, ll mult) {
	target *= mult;
	target %= MODULO;
}

ll mult(ll target, ll mult) {
    ll result = target;
    remult(result, mult);
    return result;
}

ll binpow(ll base, ll power) {
	if (0 == power) return 1;

	ll half = binpow(base, power >> 1);
	remult(half, half);

	if (power & 1) remult(half, base);

	return half;
}

//////////////////////////////////////////////////////////////////

template <typename T>
T read() {
    T value;
    cin >> value;
    return value;
}

int ri() {
    return read<int>();
}

ll rll() {
    return read<ll>();
}

string rs() {
    return read<string>();
}

template<typename T>
vector<T> rv(size_t size) {
    vector<T> a(size);
    for (size_t i = 0; i < size; ++i) {
        a[i] = read<T>();
    }
    return a;
}

//////////////////////////////////////////////////////////////////

template<typename T>
void compress(vector<T>& values) {
	sort(values.begin(), values.end());
	values.erase(unique(values.begin(), values.end()), values.end());
}

template<typename T, typename D>
void increase(vector<T>& values, D delta) {
    for (T& value : values) {
        value += delta;
    }
}

template<typename T>
void print(T x) {
	cout << x << ENDL;
}

template<typename T>
void print_all(const vector<T>& values, char sep = SPACE) {
	for (auto& value : values) cout << value << sep;
	if (sep != ENDL) cout << ENDL;
}

template<typename F, typename S>
void print_pair(const pair<F, S>& values) {
	cout << values.first << SPACE << values.second << ENDL;
}

bool yes_no(bool result, string yes = "YES", string no = "NO") {
	cout << (result ? yes : no) << ENDL;
	return result;
}

//////////////////////////////////////////////////////////////////

template<typename T, typename S>
bool remin(T& target, S source) {
	bool change = target > source;
	if (change) target = source;
	return change;
}

template<typename T, typename S>
bool remax(T& target, S source) {
    bool change = target < source;
	if (change) target = source;
	return change;
}

template<typename N, typename D>
N ceil_div(N numerator, D denominator) {
	return (numerator - 1) / denominator + 1;
}

//////////////////////////////////////////////////////////////////

ll for_pow(ll base, int power) {
	ll result = 1;
	for (int i = 0; i < power; ++i) result *= base;
	return result;
}

ll gcd(ll a, ll b) {
	return (0 == a) ? b : gcd(b % a, a);
}

ll lcm(ll a, ll b) {
	if (0 == a && 0 == b) return 0;
	return a / gcd(a, b) * b;
}

vi get_primes(int max_prime) {
	vector<bool> is_prime(max_prime + 1, true);
	is_prime[0] = false, is_prime[1] = false;

	vi primes;
	for (int i = 2; i <= max_prime; ++i) {
		if (is_prime[i]) {
			primes.push_back(i);
			for (int j = i + i; j <= max_prime; j += i) {
				is_prime[j] = false;
			}
		}
	}

	return primes;
}

//////////////////////////////////////////////////////////////////

vector<string> split(string& s, string seps) {
    vector<string> parts;

    string part = "";
    auto add_part = [&]() {
        parts.push_back(part);
        part = "";
    };

    for (char ch : s) {
        if (string::npos != seps.find(ch)) {
            add_part();
        } else {
            part += ch;
        }
    }

    add_part();

    return parts;
}

//////////////////////////////////////////////////////////////////


class FenwickTree {
private:
	int size;
	vll tree;
public:
	FenwickTree(int n)
	: size(n + 1)
	, tree(size, 0)
	{ }

	void update(int i, int d) {
		++i;
		for (; i < size; i += (i & -i)) {
			tree[i] += d;
		}
	}

	ll get_sum(int i) {
		ll sum = 0;

		++i;
		for (; i > 0; i -= (i & -i)) {
			sum += tree[i];
		}

		return sum;
	}

	int get_floor(int k) {
		int res = 0;
		for (int bit = 20; bit >= 0; --bit) {
			int next = res | (1 << bit);
			if (next < size && tree[next] < k) {
				res = next;
				k -= tree[next];
			}
		}
		return res;
	}
};

//////////////////////////////////////////////////////////////////

struct DSU {
	vector<size_t> parents;
	vector<size_t> sizes;
	vector<size_t> ranks;

	DSU(size_t n = 1) {
		resize(n);
	}

	void resize(size_t n) {
		parents.resize(n);
		for (size_t v = 0; v < n; ++v) {
			parents[v] = v;
		}

		ranks.resize(n, 1);
		sizes.resize(n, 0);
	}

	size_t get(size_t v) {
		size_t parent = parents[v];
		if (parent == v) return v;

		return parents[v] = get(parent);
	}

	bool merge(size_t f, size_t t, size_t weight = 1, bool multiple_edges = false) {
		size_t a = get(f);
		size_t b = get(t);

		if (multiple_edges) {
			sizes[a] += weight;
		}

		if (a == b) return false;

		if (ranks[a] < ranks[b]) {
			swap(a, b);
		}

		parents[b] = a;
		if (ranks[a] == ranks[b]) ++ranks[a];
		sizes[a] += sizes[b];
		if (!multiple_edges) sizes[a] += weight;

		return true;
	}

	bool connected(size_t f, size_t t) {
		return get(f) == get(t);
	}

	size_t get_size(size_t v) {
		return sizes[get(v)];
	}

	bool is_root(size_t v) {
		return v == get(v);
	}
};

//////////////////////////////////////////////////////////////////

ld sqrt_ld(ld value) {
    return sqrt(value);
}

//////////////////////////////////////////////////////////////////

int get_bit(ll mask, int bit) {
	return (mask >> bit) & 1;
}

//////////////////////////////////////////////////////////////////

#define NONLINE_JUDGE

#define FACEBOOK_HACKER_CUP

#ifdef ONLINE_JUDGE
#define NFILE_IO
#endif

void init_io() {
    string fn = "";
    string in_fn = "", out_fn = "";

    string basic_files_directory = "../../";


    #ifndef ONLINE_JUDGE
    in_fn = basic_files_directory + "input.txt"; // reading from file in parent of parent of directory with file
    out_fn = basic_files_directory + "output.txt";
    #endif

    #ifdef FILE_IO
    in_fn = "input.txt";
    out_fn = "output.txt";
    #endif

    if (!fn.empty()) {
		in_fn = fn + ".in";
		out_fn = fn + ".out";
	}

	if (!in_fn.empty()) {
		freopen(in_fn.c_str(), "rt", stdin);

		#ifdef FACEBOOK_HACKER_CUP
		string real_in_fn = rs();
		cout << real_in_fn << endl;
		if ("input" != real_in_fn) {
			real_in_fn = basic_files_directory + real_in_fn + ".txt";
			freopen(real_in_fn.c_str(), "rt", stdin);
		}
		#endif
	}

	if (!out_fn.empty()) {
		freopen(out_fn.c_str(), "wt", stdout);
	}

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

using graph_t = vvi;

void precalc() {

}

void solve_test() {

}

void solve() {
    #ifdef FACEBOOK_HACKER_CUP:
	    int t = ri();
        for (int test_index = 1; test_index <= t; ++test_index) {
            #ifdef FACEBOOK_HACKER_CUP
            cout << "Case #" << test_index << ": ";
            #endif

            solve_test();
        }
    #endif
}

signed main() {
    init_io();

    #ifdef STRESS

    stress();

    #else

    precalc();

	int tests =
	#ifdef FACEBOOK_HACKER_CUP
		1;
	#elif LOCAL
		ri();
	#else
		1;
	#endif

	while (tests --> 0) {
		solve();
	}
	#endif

    return 0;
}

