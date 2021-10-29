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

bool is_correct_length(string& s, int max_length) {
    return !s.empty() && s.length() <= max_length;
}

bool is_correct_char(char ch) {
    if (isalpha(ch)) return true;
    if (isdigit(ch)) return true;
    return '_' == ch;
}

bool is_correct_word(string& s, int max_length) {
    if (!is_correct_length(s, max_length)) return false;

    for (char ch : s) {
        if (!is_correct_char(ch)) return false;
    }

    return true;
}

bool is_correct(string& id) {
    int at_index = id.find('@');
    if (string::npos == at_index) return false;

    string user_name = id.substr(0, at_index);
    if (!is_correct_word(user_name, 16)) return false;

    int slash_index = id.find('/');
    if (string::npos == slash_index) {
        slash_index = id.length();
    }

    string host_name = id.substr(at_index + 1, slash_index - at_index - 1);
    if (!is_correct_length(host_name, 32)) return false;

    vector<string> host_name_parts = split(host_name, ".");
    for (string& part : host_name_parts) {
        if (!is_correct_word(part, 16)) return false;
    }

    if (slash_index < id.length()) {
        string resource = id.substr(slash_index + 1, id.length() - slash_index - 1);
        return is_correct_word(resource, 16);
    } else {
        return true;
    }
}

void solve() {
    string id;
    getline(cin, id);

    bool ans = is_correct(id);
    yn(ans);
}

int main() {
    init_io();
    solve();
    return 0;
}