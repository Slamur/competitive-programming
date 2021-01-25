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

vector<int> calc_counts(string& s) {
    vector<int> counts(1 << 8, 0);
    for (char ch : s) {
        counts[ch]++;
    }

    return counts;
}

int get_max_times(vector<int>& counts_source, vector<int>& counts_target) {
	int max_times = numeric_limits<int>::max();
	
	for (char ch = 'a'; ch <= 'z'; ++ch) {
		int source_count = counts_source[ch];
		int target_count = counts_target[ch];
		
		if (source_count < 0) return -1;
		if (target_count == 0) continue;
		
		max_times = min(max_times, source_count / target_count);
	}
	
	return max_times;
}
		

string get_ans(string& a, string& b, string& c) {
    vector<int> a_counts = calc_counts(a);
    vector<int> b_counts = calc_counts(b);
    vector<int> c_counts = calc_counts(c);

    int best_b = 0, best_c = 0;
    
    int max_b = get_max_times(a_counts, b_counts);
	vector<int> a_no_b_counts(1 << 8);
	
    for (int b_times = 0; b_times <= max_b; ++b_times) {
		
		for (char ch = 'a'; ch <= 'z'; ++ch) {
			a_no_b_counts[ch] = a_counts[ch] - b_counts[ch] * b_times;
		}
		
        int c_times = get_max_times(a_no_b_counts, c_counts);
        if (c_times < 0) continue;

        if (best_b + best_c < b_times + c_times) {
            best_b = b_times;
            best_c = c_times;
        }
    }
    
    string ans = "";
    for (int b_times = 0; b_times < best_b; ++b_times) {
        ans += b;
    }

    for (int c_times = 0; c_times < best_c; ++c_times) {
        ans += c;
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        int not_used = a_counts[ch] - b_counts[ch] * best_b - c_counts[ch] * best_c;
        ans += string(not_used, ch);
    }

    return ans;
}

void solve() {
    string a = rs();
    string b = rs();
    string c = rs();

    string answer = get_ans(a, b, c);
    cout << answer << ENDL;
}

int main() {
    init_io();
    solve();
    return 0;
}
