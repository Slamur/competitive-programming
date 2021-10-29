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

string get_ans(string& s) {
    string ans = "";

    vector<string> parts = split(s, " ");
    for (string& part : parts) {
        if (part.length() == 0) continue;

        if (ans.length() > 0 && ans.back() != SPACE) {
            ans += SPACE;
        }

        for (char ch : part) {
            if (!isalpha(ch)) {
                if (ans.back() == SPACE) ans.pop_back();
                ans += ch;
                ans += SPACE;
            } else {
                ans += ch;
            }
        }
    }

    return ans;
}

void solve() {
    string s;
    getline(cin, s);

    string ans = get_ans(s);
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}