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

string get_ans(string& s, string& t) {
    vector<int> s_counts(1 << 8, 0);
    for (char ch : s) s_counts[ch]++;

    char none = '\0';
    while (t.length() < s.length()) {
        t += none;
    }

    string no_ans = "";

    string ans(s.length(), none);
    auto can_be_greater = [&](int start_index, char start_ch) {
        ans[start_index] = start_ch;
        --s_counts[start_ch];

        int index = start_index + 1;
        for (char ch = 'z'; ch >= 'a'; --ch) {
            for (int it = 0; it < s_counts[ch]; ++it) {
                ans[index++] = ch;
            }
        }

        bool can = (t < ans);

        ++s_counts[start_ch];
        ans[start_index] = none;

        return can;
    };

    bool prefix_equals = true;
    for (int index = 0; index < s.length(); ++index) {
        char start_ch = 'a';

        char t_ch = t[index];
        if (prefix_equals && none != t_ch) {
            start_ch = t_ch;
        }

        char used_ch = none;

        for (char ch = start_ch; ch <= 'z'; ++ch) {
            if (s_counts[ch] == 0) continue;

            if (can_be_greater(index, ch)) {
                used_ch = ch;
                break;
            }
        }

        if (none == used_ch) return "";

        prefix_equals &= (t_ch == used_ch);
        --s_counts[used_ch];
        ans[index] = used_ch;
    }

    return ans;
}

void solve() {
    string s = rs();
    string t = rs();

    string ans = get_ans(s, t);

    if (ans <= t) ans = "-1";
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}