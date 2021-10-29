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

int get_ans(string& hidden, vector<string>& words) {
    const char unknown = '*';

    vector<bool> revealed(1 << 8, false);
    for (char ch : hidden) {
        if (unknown != ch) {
            revealed[ch] = true;
        }
    }

    vector<int> counts(1 << 8, 0);
    int active_words_count = 0;

    for (string& word : words) {

        bool possible = true;
        for (int i = 0; i < word.length(); ++i) {
            char word_ch = word[i];
            char hidden_ch = hidden[i];
            if (unknown == hidden_ch) {
                possible &= !revealed[word_ch];
            } else {
                possible &= (word_ch == hidden_ch);
            }
        }

        if (!possible) continue;

        active_words_count++;

        vector<bool> waiting(1 << 8, false);
        for (char ch : word) {
            if (!revealed[ch]) waiting[ch] = true;
        }

        for (char ch = 'a'; ch <= 'z'; ++ch) {
            if (waiting[ch]) {
                counts[ch]++;
            }
        }
    }

    int ans = 0;

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (active_words_count == counts[ch]) {
            ++ans;
        }
    }

    return ans;
}

void solve() {
    ri(); // len
    string hidden = rs();

    int m = ri();
    vector<string> words = rv<string>(m);

    int ans = get_ans(hidden, words);
    cout << ans << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}