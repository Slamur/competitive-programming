#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using ld = long double;
using ii = pair<int, int>;

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
vector<T> rv(int size) {
    vector<T> a(size);
    for (int i = 0; i < size; ++i) {
        a[i] = read<T>();
    }
    return a;
}

//////////////////////////////////////////////////////////////////

bool yn(bool result, string yes = "YES", string no = "NO") {
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

void init_io() {
    string file_name = "";
    if (!file_name.empty()) {
        string input_file_name = file_name + ".in";
        freopen(input_file_name.c_str(), "rt", stdin);

        string output_file_name = file_name + ".out";
        freopen(output_file_name.c_str(), "wt", stdout);
    } else {
        #ifndef ONLINE_JUDGE
        string input_file_name = "../../input.txt"; // reading from file in parent of parent of directory with file
        freopen(input_file_name.c_str(), "rt", stdin);
        #endif
    }

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

bool get_ans(string& s, int k) {
    const char unknown = '?';
    vector<char> values(k, unknown);

    for (int i = 0; i < s.length(); ++i) {
        char actual = s[i];
        if (unknown == actual) continue;

        int group = i % k;
        char expected = values[group];

        if (unknown == expected) {
            values[group] = actual;
        } else if (expected != actual) {
            return false;
        }
    }

    const char zero = '0', one = '1';

    int balance = 0;
    for (char value : values) {
        if (zero == value) --balance;
        if (one == value) ++balance;
    }

    for (char value : values) {
        if (unknown == value) {
            if (balance < 0) ++balance;
            else --balance;
        }
    }

    return balance == 0;
}

void solve_test() {
    ri(); // n
    int k = ri();
    string s = rs();

    bool can = get_ans(s, k);
    yn(can);
}

void solve() {
    int t = ri();
    for (int test = 0; test < t; ++test) {
        solve_test();
    }
}

int main() {
    init_io();
    solve();
    return 0;
}