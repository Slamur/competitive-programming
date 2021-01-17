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
    } else {
		#ifndef ONLINE_JUDGE
		string input_file_name = "../../input.txt";
        freopen(input_file_name.c_str(), "rt", stdin);
		#endif
	}

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

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

ii get_answer(string& s) {
    int max_len_out = 0;
    int count_in = 0;

    vector<string> bracket_parts = split(s, "()");
    for (size_t part_index = 0; part_index < bracket_parts.size(); ++part_index) {
        string& part = bracket_parts[part_index];

        bool outside = (part_index % 2 == 0), inside = !outside;

        vector<string> words = split(part, "_");
        for (string& word : words) {
			if (0 == word.length()) continue;
			
            if (inside) {
                count_in++;
            }

            if (outside) {
                max_len_out = max(max_len_out, (int)word.length());
            }
        }
    }

    return make_pair(max_len_out, count_in);
}

void solve() {
	ri(); // unused length of s
    string s = rs();
	
    ii ans = get_answer(s);
    cout << ans.first << SPACE << ans.second << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}
