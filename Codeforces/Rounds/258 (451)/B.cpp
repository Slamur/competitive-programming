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

#define NONLINE_JUDGE

#ifdef ONLINE_JUDGE
#define NFILE_IO
#endif

void init_io() {
    string fn = "";
    string in_fn = "", out_fn = "";

    string basic_files_directory = "";

    #ifndef ONLINE_JUDGE
    in_fn = basic_files_directory + "input.txt";
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
	}

	if (!out_fn.empty()) {
		freopen(out_fn.c_str(), "wt", stdout);
	}

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

ii get_answer(int n, vi& a) {
	vi sorted_a(a.begin(), a.end());
	sort(sorted_a.begin(), sorted_a.end());
	
	int start = n, end = 0;
	for (int i = 0; i < n; ++i) {
		if (a[i] != sorted_a[i]) {
			start = i;
			break;
		}
	}
	
	for (int i = n; i > 0; --i) {
		if (a[i - 1] != sorted_a[i - 1]) {
			end = i;
			break;
		}
	}
	
	if (start > end) {
		return make_pair(0, 0);
	}
	
	reverse(a.begin() + start, a.begin() + end);
	
	return (a == sorted_a)
		? make_pair(start, end - 1)
		: make_pair(-1, -1);
}

void solve() {
	int n = ri();
	vi a = rv<int>(n);
	
	const auto& [start, end] = get_answer(n, a);
	if (yes_no(-1 != start, "yes", "no")) {
		print_pair(make_pair(start + 1, end + 1));
	}
}

signed main() {
 	init_io();
	solve();
	return 0;
}
