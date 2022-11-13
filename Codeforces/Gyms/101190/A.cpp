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

vector<string> parse(const string& line) {
	vector<string> tokens;
	string token = "";
	
	auto add_token = [&]() {
		if (token.size() > 0) {
			tokens.push_back(token);
		}
		token = "";
	};
	
	for (char ch : line) {
		if (!isalpha(ch)) {
			add_token();
		}
		
		token += ch;
		
		if (!isalpha(ch)) {
			add_token();
		}
	}
	
	add_token();
	
	return tokens;
}

const string PUNCTUATION = ",.";
const string SPACE = " ";

bool is_punctuation(const string& token) {
	return PUNCTUATION.find(token) != string::npos;
}

bool is_space(const string& token) {
	return SPACE == token;
}

bool is_word(const string& token) {
	return isalpha(token.front());
}

bool is_capitalized(const string& word) {
	bool first_upper = isupper(word.front());
	
	bool suffix_lower = word.size() > 1;
	for (int i = 1; i < word.size(); ++i) {
		if (!islower(word[i])) {
			suffix_lower = false;
		}
	}
	
	return first_upper && suffix_lower;
}

vector<vector<string>> calc_blocks(const vector<string>& tokens) {
	vector<vector<string>> blocks;
	
	bool open = false;
	auto add_single = [&](const string& token) {
		blocks.emplace_back(1, token);
		open = false;
	};
	
	auto get_last = [&]() {
		return blocks.back().back();
	};
	
	auto add_last = [&](const string& token) {
		blocks.back().push_back(token);		
	};
	
	for (auto& token : tokens) {
		if (is_punctuation(token)) {
			add_single(token);
		}
		
		if (is_space(token)) {
			if (open && is_word(get_last())) {
				add_last(token);
			} else {
				add_single(token);
			}
		}
		
		if (is_word(token)) {
			if (is_capitalized(token)) {
				if (open && is_space(get_last())) {
					add_last(token);
				} else {		
					add_single(token);
					open = true;
				}			
			} else {
				add_single(token);
			}
		}
	}
	
	return blocks;
}

void print_blocks(vector<vector<string>>& blocks) {
	for (auto& block : blocks) {		
		bool spaced = false;
		if (block.size() % 2 == 0) {
			spaced = true;
			block.pop_back();
		}
		
		if (block.size() == 1) {
			cout << block.front();
		} else {
			string abbreviation = "";
			for (auto& token : block) {
				if (is_word(token)) {
					abbreviation += token.front();
				}
			}
			
			cout << abbreviation << SPACE;
			cout << "(";
			for (auto& token : block) {
				cout << token;
			}
			cout << ")";
		}
		
		if (spaced) {
			cout << SPACE;
		}
	}
	cout << endl;
}

void solve() {
	string line;
	while (getline(cin, line)) {
		vector<string> tokens = parse(line);
		
		vector<vector<string>> blocks = calc_blocks(tokens);
		
		print_blocks(blocks);
	}
}

int main() {
	init_io("abbreviation");
    	solve();
	
	return 0;
}
