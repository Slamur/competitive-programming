#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using ld = long double;

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

pair<string, int> get_ans(string& s) {
    string best_s = s;
    int best_k = 1;

    for (int k = 2, n = s.length(); k <= n; ++k) {
        string suffix = s.substr(k - 1, n - (k - 1));
        string prefix = s.substr(0, k - 1);
        if (suffix.length() % 2 == 1) {
            reverse(prefix.begin(), prefix.end());
        }

        string total = suffix + prefix;
        if (best_s > total) {
            best_s = total;
            best_k = k;
        }
    }

    return make_pair(best_s, best_k);
}

void solve_test() {
    ri(); // n
    string s = rs();

    pair<string, int> ans = get_ans(s);
    cout << ans.first << ENDL << ans.second << ENDL;
}

void solve() {
    int tests = ri();
    for (int test = 0; test < tests; ++test) {
        solve_test();
    }
}

int main() {
    init_io();
    solve();
    return 0;
}