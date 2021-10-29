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

bool is_good(int year) {
    vector<int> counts(10, 0);
    for (; year > 0; year /= 10) {
        int last = year % 10;
        counts[last]++;
    }

    for (int count : counts) {
        if (count > 1) return false;
    }

    return true;
}

int get_answer(int cur_year) {
    for (int year = cur_year + 1; ; ++year) {
        if (is_good(year)) {
            return year;
        }
    }
}

void solve() {
    int cur_year = ri();
    int answer = get_answer(cur_year);
    cout << answer << endl;
}

int main() {
    init_io();
    solve();
    return 0;
}