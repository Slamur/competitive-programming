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

string substr(string& s, int start_inclusive, int end_exclusive) {
    return s.substr(start_inclusive, end_exclusive - start_inclusive);
}

string get_answer(string& number) {
    int dotIndex = number.find(".");

    if (string::npos == dotIndex) {
        dotIndex = number.length();
        number += ".0";
    }

    if (0 == dotIndex) {
        dotIndex = 1;
        number = "0" + number;
    }

    string integerPart = substr(number, 0, dotIndex);
    string floatPart = substr(number, dotIndex + 1, number.length());

    string numberWithoutDot = integerPart + floatPart;

    int firstNotZeroIndex = 0;
    while (firstNotZeroIndex < numberWithoutDot.length() && '0' == numberWithoutDot[firstNotZeroIndex]) {
        ++firstNotZeroIndex;
    }

    int lastNotZeroIndex = numberWithoutDot.length() - 1;
    while (lastNotZeroIndex >= 0 && '0' == numberWithoutDot[lastNotZeroIndex]) {
        --lastNotZeroIndex;
    }

    int expectedDotIndex = firstNotZeroIndex + 1;
    int exponent = dotIndex - expectedDotIndex;

    string answer = "";
    answer += numberWithoutDot[firstNotZeroIndex];

    if (firstNotZeroIndex != lastNotZeroIndex) {
        answer += ".";
    }

    for (int index = firstNotZeroIndex + 1; index <= lastNotZeroIndex; ++index) {
        answer += numberWithoutDot[index];
    }

    if (exponent != 0) {
        answer += "E";
        answer += to_string(exponent);
    }

    return answer;
}

void solve() {
    string number = rs();
    string answer = get_answer(number);
    cout << answer << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}