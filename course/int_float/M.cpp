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

int get_type_index(string number){
    vector<string> limits = {
            "127", "32767", "2147483647", "9223372036854775807"
    };

    for (int typeIndex = 0; typeIndex < limits.size(); ++typeIndex) {
        string& limit = limits[typeIndex];

        bool correct = number.length() < limit.length();
        correct |= (number.length() == limit.length() && number <= limit);

        if (correct) {
            return typeIndex;
        }
    }

    return limits.size();
}

void solve() {
    string number = rs();

    int typeIndex = get_type_index(number);

    vector<string> types = {
            "byte", "short", "int", "long", "BigInteger"
    };

    cout << types[typeIndex] << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}