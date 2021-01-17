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
        string input_file_name = "../../input.txt"; // reading from file in the same directory
        freopen(input_file_name.c_str(), "rt", stdin);
        #endif
    }

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

string signs = "-;_";

string refine(string& s) {
    string refined = "";
    for (char& ch : s) {
        if (string::npos != signs.find(ch)) continue;

        refined += tolower(ch);
    }

    return refined;
}

vector<bool> get_ans(vector<string>& parts, vector<string>& queries) {
    for (string& part : parts) {
        part = refine(part);
    }

    string a = parts[0], b = parts[1], c = parts[2];

    vector<string> permutations = {
        a + b + c,
        a + c + b,
        b + a + c,
        b + c + a,
        c + a + b,
        c + b + a
    };

    int q = queries.size();
    vector<bool> answers(q, false);

    for (int i = 0; i < q; ++i) {
        string query = refine(queries[i]);

        bool answer = false;
        for (string& p : permutations) {
            answer |= (p == query);
        }

        answers[i] = answer;
    }

    return answers;
}

void solve() {
    int n = 3;
    vector<string> parts(n);
    for (string& part : parts) {
        part = rs();
    }

    int q = ri();
    vector<string> queries(q);
    for (string& query : queries) {
        query = rs();
    }

    vector<bool> answers = get_ans(parts, queries);
    for (bool answer : answers) {
        yn(answer, "ACC", "WA");
    }
}

int main() {
    init_io();
    solve();
    return 0;
}
