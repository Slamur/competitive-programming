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
    } else {
        #ifndef ONLINE_JUDGE
        string input_file_name = "input.txt"; // reading from file in the same directory
        freopen(input_file_name.c_str(), "rt", stdin);
        #endif
    }

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

string get_ans(string& s, int k) {
    string ans = s;

    for (char& ch : ans) { // & changes char in string
        int left = ch - 'a';
        int right = 'z' - ch;

        int can_left = min(left, k);
        int can_right = min(right, k);

        if (can_left > can_right) {
            ch -= can_left;
            k -= can_left;
        } else {
            ch += can_right;
            k -= can_right;
        }
    }

    return (k > 0) ? "-1" : ans;
}

void solve() {
    ri(); // n
    int k = ri();
    string s = rs();

    string ans = get_ans(s, k);
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}