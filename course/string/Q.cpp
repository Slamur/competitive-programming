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

ll get_ans(string& a, string& b) {
    int a_len = a.length(), b_len = b.length();
    int window_size = b_len - a_len + 1;

    vector<int> counts(2, 0);
    for (int i = 0; i < window_size; ++i) {
        int b_value = b[i] - '0';
        counts[b_value]++;
    }

    ll ans = 0;
    for (int i = 0; i < a_len; ++i) {
        int a_value = a[i] - '0';
        ans += counts[1 - a_value];

        int left_b_value = b[i] - '0';
        counts[left_b_value]--;

        if (i + window_size < b_len) {
            int right_b_value = b[i + window_size] - '0';
            counts[right_b_value]++;
        }
    }

    return ans;
}

void solve() {
    string a = rs();
    string b = rs();

    ll ans = get_ans(a, b);
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}