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

ll get_answer(ll a, ll b, ll k) {
    ll answer = 0;
    for (ll y = 1; ; ++y) {
        ll y3 = y * y * y;
        if (y3 < a) continue;
        if (b < y3) break;

        ll leftX2 = max(y3 - k, a);
        ll rightX2 = min(y3 + k, b);

        ll leftX = sqrt_ld(leftX2);
        if (leftX * leftX < leftX2) ++leftX;

        ll rightX = sqrt_ld(rightX2);

        if (leftX <= rightX) {
            answer += rightX - leftX + 1;
        }
    }

    return answer;
}

void solve() {
    ll a = rll();
    ll b = rll();
    ll k = rll();

    ll answer = get_answer(a, b, k);
    cout << answer << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}