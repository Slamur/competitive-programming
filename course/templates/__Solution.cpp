#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vll = vector<ll>;
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

bool yesNo(bool result, string yes = "YES", string no = "NO") {
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

ld sqrt_ld(ld value) {
    return sqrt(value);
}

//////////////////////////////////////////////////////////////////

int get_bit(ll mask, int bit) {
	return (mask >> bit) & 1;
}

//////////////////////////////////////////////////////////////////

void init_io() {
    string fn = "";
    string in_fn = "", out_fn = "";

    #ifndef ONLINE_JUDGE
    in_fn = "../../input.txt"; // reading from file in parent of parent of directory with file
    //out_fn = "../../output.txt";
    #endif

    if (!fn.empty()) {
		in_fn = fn + ".in";
		out_fn = fn + ".out";
	}

	if (!in_fn.empty()) {
		freopen(in_fn.c_str(), "rt", stdin);
	}

	if (!out_fn.empty()) {
		freopen(out_fn.c_str(), "wt", stdout);
	}

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

using graph_t = vvi;
using ans_t = int;

void precalc() {

}

void solve_test() {

}

void solve() {
}

signed main() {
    init_io();

    #ifdef STRESS

    stress();

    #else

    precalc();

	int tests =
	#ifdef LOCAL
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
