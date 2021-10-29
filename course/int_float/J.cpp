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

int sign(ll x) {
    if (x < 0) return -1;
    if (x > 0) return 1;
    return 0;
}

void solve() {
    ll a1 = rll(), b1 = rll();
    ll a2 = rll(), b2 = rll();
    /*
    t1 = t2
    t1 = (b1 + a1) / v1, t2 = (b2 + a2) / v2

    (b1 + a1) * v2 == (b2 + a2) * v1
    v1 / v2 == (b1 + a1) / (b2 + a2)

    -> a1 / v1 ? a2 / v2
    a1 / a2 ? v1 / v2

    (!) a1 / a2 ? (b1 + a1) / (b2 + a2)

    a1 * b2 + a1 * a2 ? b1 * a2 + a1 * a2
    (!!!) a1 * b2 ? b1 * a2
     */

    ll first = a1 * b2;
    ll second = b1 * a2;

    vector<string> answers = { "First", "Draw", "Second" };

    int cmp = sign(first - second);
    cout << answers[cmp + 1] << endl;
}

int main() {
    init_io();
    solve();
    return 0;
}