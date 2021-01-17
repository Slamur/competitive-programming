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
    }

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

string get_answer(string& s) {
    for (int i = 1; i < s.length(); ++i) {
        if (islower(s[i])) return s;
    }

    char& first = s[0]; // char& changes s[0] too
    if (islower(first)) first = toupper(first);
    else first = tolower(first);

    for (int i = 1; i < s.length(); ++i) {
        s[i] = tolower(s[i]);
    }

    return s;
}

void solve() {
    string s = rs();

    string ans = get_answer(s);
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}