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

ll get_answer(ll damage, ll heal_per_second, ll heal_duration, ll cooldown) {
    if (damage > heal_per_second * heal_duration) return -1;

    ll heal_per_cooldown = heal_per_second * cooldown;

    /*
    f(k) = damage * k - heal_per_cooldown * (k * (k - 1) / 2)
    f(k) = -heal_per_cooldown / 2 * k^2 + k * (damage + heal_per_cooldown / 2)

    kOpt = -b / (2a) = -(damage + heal_per_cooldown / 2) / (-heal_per_cooldown / 2 * 2)
    kOpt = (2 * damage + heal_per_cooldown) / (2 * heal_per_cooldown)

    k in [1; heal_duration / cooldown + 1]
     */

    ll answer = 0;

    ll kOpt = (2 * damage + heal_per_cooldown) / (2 * heal_per_cooldown);
    for (ll k = max(1LL, kOpt - 1); k <= min(heal_duration / cooldown + 1, kOpt + 1); ++k) {
        ll maxHp = damage * k - heal_per_cooldown * (k * (k - 1) / 2);
        answer = max(answer, maxHp);
    }

    return answer;
}

void solve_test() {
    ll damage = rll(), heal_per_second = rll();
    ll heal_duration = rll(), cooldown = rll();

    ll answer = get_answer(damage, heal_per_second, heal_duration, cooldown);
    cout << answer << ENDL;
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