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

ii get_ans(string& s, string& t) {
    char start = 'a', end = 'z';
    int size = end - start + 1;

    vector<int> s_counts(size, 0);
    for (char ch : s) {
        s_counts[ch - start]++;
    }

    vector<int> t_counts(size, 0);
    for (char ch : t) {
        t_counts[ch - start]++;
    }

    ii need_tree = { false, false };

    bool need_remove = false;
    for (int ch = 0; ch < size; ++ch) {
        int delta = s_counts[ch] - t_counts[ch];

        if (delta < 0) return need_tree;

        if (delta > 0) {
            need_remove = true;
        }
    }

    int ti = 0;
    for (int si = 0; si < s.length() && ti < t.length(); ++si) {
        if (s[si] == t[ti]) {
            ++ti;
        }
    }

    bool need_swap = (ti != t.length());

    return { need_remove, need_swap } ;
}

void solve() {
    string s = rs();
    string t = rs();

    ii ans = get_ans(s, t);

    vector<string> ans_names = {
        "need tree", "automaton", "array", "both"
    };

    int name_index = (ans.first << 0) | (ans.second << 1);
    cout << ans_names[name_index] << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}