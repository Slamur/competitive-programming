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

pair<bool, vector<bool>> no_answer(false, vector<bool>(0));

pair<bool, vector<bool>> get_ans(string& prefix, string& suffix, vector<string>& words, vector<ii>& len_to_indexes) {
    int total_len = prefix.length() + 1;

    string pref_common = prefix.substr(1, total_len - 2);
    string suff_common = suffix.substr(0, total_len - 2);

    if (pref_common != suff_common) {
        return no_answer;
    }

    string total = prefix + suffix.back();

    vector<bool> is_suffixes(words.size());
    for (int len = 1; len < total_len; ++len) {
        int first = len_to_indexes[len].first, second = len_to_indexes[len].second;
        string& first_word = words[first];
        string& second_word = words[second];

        string total_pref = total.substr(0, len);
        string total_suff = total.substr(total_len - len, len);

        bool first_pref = (first_word == total_pref);
        bool first_suff = (first_word == total_suff);

        bool second_pref = (second_word == total_pref);
        bool second_suff = (second_word == total_suff);

        if (first_pref && second_suff) {
            is_suffixes[first] = false;
            is_suffixes[second] = true;
        } else if (first_suff && second_pref) {
            is_suffixes[first] = true;
            is_suffixes[second] = false;
        } else {
            return no_answer;
        }
    }

    return { true, is_suffixes };
}

vector<bool> get_is_suffixes(vector<string>& words) {
    int length = words.size() / 2 + 1;

    vector<ii> len_to_indexes(length, { -1, -1 });
    for (int i = 0; i < words.size(); ++i) {
        string& word = words[i];
        int len = word.length();

        ii& indexes = len_to_indexes[len];
        if (-1 == indexes.first) indexes.first = i;
        else indexes.second = i;
    }

    string& max1 = words[len_to_indexes[length - 1].first];
    string& max2 = words[len_to_indexes[length - 1].second];

    auto ans12 = get_ans(max1, max2, words, len_to_indexes);
    auto ans21 = get_ans(max2, max1, words, len_to_indexes);

    return ans12.first ? ans12.second : ans21.second;
}

void solve() {
    int n = ri();
    int size = 2 * n - 2;
    vector<string> words = rv<string>(size);

    vector<bool> is_suffixes = get_is_suffixes(words);
    for (bool is_suffix : is_suffixes) {
        cout << (is_suffix ? 'S' : 'P');
    }
    cout << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}