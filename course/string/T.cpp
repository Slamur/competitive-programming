#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using ld = long double;
using ii = pair<int, int>;

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

template<typename T>
vector<T> rv(int size) {
    vector<T> a(size);
    for (int i = 0; i < size; ++i) {
        a[i] = read<T>();
    }
    return a;
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

int get_ans(string s) {
    int start_length = s.length();

    for (char removed_ch = 'z'; removed_ch >= 'a'; --removed_ch) {
        for (int direction = 0; direction < 2; ++direction) {
            string builder = "";
            for (char ch : s) {
                bool removed = false;

                if (ch == removed_ch) {
                    if (builder.length() > 0) {
                        char builder_last = builder.back();
                        if (builder_last == removed_ch - 1) {
                            removed = true;
                        }
                    }
                }

                if (!removed) {
                    builder += ch;
                }
            }

            reverse(builder.begin(), builder.end());
            s = builder;
        }
    }

    return start_length - s.length();
}

void solve() {
    ri(); // n
    string s = rs();

    int ans = get_ans(s);
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}