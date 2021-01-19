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

bool get_ans(string& a, string& b, int k) {
    char start = 'a', end = 'z';
    int size = end - start + 1;

    vector<int> aCounts(size, 0);
    vector<int> bCounts(size, 0);

    for (char ch : a) aCounts[ch - start]++;
    for (char ch : b) bCounts[ch - start]++;

    for (int ch = 0; ch < size - 1; ++ch) {
        int needRemove = aCounts[ch] - bCounts[ch];
        if (needRemove < 0) return false;
        if (needRemove % k != 0) return false;

        aCounts[ch + 1] += needRemove;
    }

    return true;
}

void solve_test() {
    ri(); // n
    int k = ri();
    string a = rs();
    string b = rs();

    bool can = get_ans(a, b, k);
    yn(can);
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