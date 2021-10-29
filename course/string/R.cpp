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

string get_ans(string& s, int k) {
    vector<bool> used(1 << 8, false);
    for (char ch : s) {
        used[ch] = true;
    }

    char min_used = '\0';
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (used[ch]) {
            min_used = ch;
            break;
        }
    }

    int n = s.length();

    string t(k, '\0');
    for (int i = 0, size = min(n, k); i < size; ++i) {
        t[i] = s[i];
    }

    if (n < k) {
        for (int i = n; i < k; ++i) t[i] = min_used;
    } else {
        char max_used = '\0';
        for (char ch = 'z'; ch >= 'a'; --ch) {
            if (used[ch]) {
                max_used = ch;
                break;
            }
        }

        int changed_index = -1;
        for (int i = k - 1; i >= 0; --i) {
            if (t[i] != max_used) {
                changed_index = i;
                break;
            }
        }

        for (char next_ch = t[changed_index] + 1; next_ch <= 'z'; ++next_ch) {
            if (used[next_ch]) {
                t[changed_index] = next_ch;
                break;
            }
        }

        for (int i = changed_index + 1; i < k; ++i) {
            t[i] = min_used;
        }
    }

    return t;
}

void solve() {
    ri(); // n;
    int k = ri();
    string s = rs();

    string t = get_ans(s, k);
    cout << t << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}