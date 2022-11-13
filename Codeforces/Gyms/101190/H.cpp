#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;

void init_io(const string& filename) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	if (filename.size() > 0) {
	    freopen((filename + ".in").c_str(), "rt", stdin);
	    freopen((filename + ".out").c_str(), "wt", stdout);   
	}
}

const char SPACE = ' ';
const string X = "x";
const string GREATER = ">=", LESS = "<=";
const string OR = "||", AND = "&&";

vector<string> split(const string& line) {
	vector<string> tokens;
	string token = "";
	
	auto add_token = [&]() {
		if (token.size() > 0) {
			tokens.push_back(token);
		}
		token = "";	
	};
	
	for (char ch : line) {
		if (SPACE == ch) add_token();
		else token += ch;
	}
	
	add_token();
	
	return tokens;
}

vector<string> parse(const string& line) {
	vector<string> parts = split(line);
	
	vector<string> tokens;
	
	for (auto& part : parts) {
		char first = part.front();
		if (isdigit(part.back()) || GREATER == part || LESS == part) {
			tokens.push_back(part);
		}
	}
	
	return tokens;
}

void solve() {
	vector<string> lines;
	
	string input_line;
	while (getline(cin, input_line)) {
		lines.push_back(input_line);
	}
	
	int min_value = -(1 << 15), max_value = (1 << 15) - 1;

	vector<pair<int, int>> segments;

	for (auto& line : lines) {
		vector<string> tokens = parse(line);
		
		int left = min_value, right = max_value;
		for (int i = 0; i < tokens.size(); i += 2) {	
			stringstream str_to_int;
			str_to_int << tokens[i + 1];
			
			int value;
			str_to_int >> value;
					
			if (tokens[i] == GREATER) {
				left = value;
			} else {
				right = value;
			}
		}
					
		if (left <= right) {
			segments.emplace_back(left, right);
		}
	}
	
	int shift = -min_value, size = (max_value - min_value + 1);
	
	vi deltas(size + 1, 0);
	for (auto& [left, right] : segments) {
		deltas[left + shift]++;
		deltas[right + shift + 1]--;
	}
	
	for (int i = 1; i < deltas.size(); ++i) {
		deltas[i] += deltas[i - 1];
	}
	
	vector<pair<int, int>> ans_segments;
	
	int last_start = -1;
	for (int i = 0; i < deltas.size(); ++i) {
		if (deltas[i] == 0) {
			if (last_start != -1) {
				ans_segments.emplace_back(last_start, i - 1);
			last_start = -1;
			}
		} else {
			if (last_start == -1) {
				last_start = i;
			}
		}
	}
	
	vector<pair<int, int>> all(1, { 0, size - 1 });
	
	if (ans_segments.size() == 0) {
		cout << "false" << endl;
	} else if (ans_segments == all) {
		cout << "true" << endl;
	} else {
		for (int i = 0; i < ans_segments.size(); ++i) {
			auto& segment = ans_segments[i];
			int left = segment.first - shift;
			int right = segment.second - shift;
			
			string res = "";
		
			auto add_part = [&](const string& sign, int value) {
				if (res.size() > 0) {
					res += SPACE;
					res += AND;
					res += SPACE;
				}
				
				res += X;
				res += SPACE;
				res += sign;
				res += SPACE;
				
				stringstream int_to_str;
				int_to_str << value;
				
				string value_str;
				int_to_str >> value_str;
				
				res += value_str; 
			};
						
			if (left != min_value) {
				add_part(GREATER, left);
			}
			
			if (right != max_value) {
				add_part(LESS, right);
			}
			
			if (i + 1 < ans_segments.size()) {
				res += SPACE;
				res += OR;
			}
			
			res += "\n";		
			cout << res;
		}
	}
}

int main() {
	init_io("hard");
    	solve();
	
	return 0;
}
