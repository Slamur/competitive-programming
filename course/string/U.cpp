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

string tolower(string s) {
    for (char& ch : s) {
        ch = tolower(ch);
    }
    return s;
}

string get_ans(string& text, vector<string>& words, char lucky_ch) {
    int n = text.length();
    vector<bool> covered(n, false);

    for (string word : words) {
        word = tolower(word);
        for (int i = 0, len = word.length(); i + len <= n; ++i) {
            if (tolower(text.substr(i, len)) == word) {
                for (int j = 0; j < len; ++j) {
                    covered[i + j] = true;
                }
            }
        }
    }

    char other_ch = ('a' == lucky_ch) ? 'b' : 'a';

    for (int i = 0; i < n; ++i) {
        if (!covered[i]) {
            continue;
        }

        char ch = text[i];
        bool is_lucky = (tolower(ch) == lucky_ch);

        char replaced_ch = is_lucky ? other_ch : lucky_ch;
        if (isupper(ch)) replaced_ch = toupper(replaced_ch);
        text[i] = replaced_ch;
    }

    return text;
}

void solve() {
    int n = ri();
    vector<string> words = rv<string>(n);
    string text = rs();
    char lucky_ch = rs()[0];

    string ans = get_ans(text, words, lucky_ch);
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}