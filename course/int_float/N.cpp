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
    int eIndex = number.find("e");

    string integerPart = substr(number, 0, dotIndex);
    string floatPart = substr(number, dotIndex + 1, eIndex);

    string exponentPart = substr(number, eIndex + 1, number.length());
    int exponent = stoi(exponentPart);

    string answer = integerPart + floatPart;

    dotIndex += exponent;

    if (dotIndex < answer.length()) {
        answer.insert(dotIndex, ".");

        string bad_tail(".0");
        while (answer.length() > 1 && string::npos != bad_tail.find(answer.back())) {
            answer.pop_back();
        }
    } else {
        int zerosNeeded = dotIndex - answer.length();

        for (int i = 0; i < zerosNeeded; ++i) {
            answer += '0';
        }
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