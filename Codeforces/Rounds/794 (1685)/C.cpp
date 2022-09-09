#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using ld = long double;
using ii = pair<int, int>;
using vi = vector<int>;

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
vector<T> rv(size_t size) {
    vector<T> a(size);
    for (size_t i = 0; i < size; ++i) {
        a[i] = read<T>();
    }
    return a;
}

//////////////////////////////////////////////////////////////////

void init_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << setprecision(10) << fixed;
}

vector<ii> get_answer(int n, vi a) {
	vi prefs(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		prefs[i + 1] = prefs[i] + a[i];
	}
	
	vi suffs(n + 2, 0);
	for (int i = n; i > 0; --i) {
		suffs[i] = suffs[i + 1] + a[i - 1];
	}
	
	deque<int> opens;
	deque<int> closes;
	
	for (int i = 0; i < n; ++i) {
		if (a[i] == 1) opens.push_back(i + 1);
		else closes.push_back(i + 1);
	}
	
	set<ii> pref_set, suff_set;
	for (int i = 1; i <= n; ++i) {
		pref_set.emplace(prefs[i], i);
		suff_set.emplace(suffs[i], i);
	}
	
	vector<ii> ans;
	
	bool inverted = false;
	int real_left = 0;
	int pref_sum = 0;
	for (int left = 1, right = n; left <= right; ) {
		if (inverted) {
			int first_close = -1, last_close = n + 1;
			bool found = false;
			int balance = 0;
			while (closes.size() > 0) {
				int close = closes.back();
				closes.pop_back();
				
				balance += (last_close - close - 1);
				if (balance >= 0) { first_close = -1; balance = 0; }
				
				if (first_close == -1) first_close = close;
				last_close = close;
				--balance;
				
				if (pref_sum + (suffs[close] - suffs[right + 1]) < 0) {
					found = true;
					break;
				}
			}
			
			if (!found) break;
			
			int first_open = -1, last_open = -1;
			balance = 0;
			while (opens.size() > 0) {
				int open = opens.front();
				opens.pop_front();
				
				balance -= (open - last_open - 1);
				if (balance >= 0) { first_open = -1; balance = 0; }
				
				if (first_open == -1) { first_open = open; }
				last_open = open;
				++balance;
				
				if (pref_sum + (suffs[open + 1] - suffs[right + 1]) < 0) {
					break;
				}
			}
			
			int open = first_open;
			int close = first_close;
			
			ans.emplace_back(real_left + (right - close) + 1, real_left + (right - open) + 1);
			
			while (opens.size() > 0 && opens.back() > close) {
				opens.pop_back();
				//++real_left;
			}
			
			real_left += right - close;
			
			while (closes.size() > 0 && closes.front() < open) {
				closes.pop_front();
				//--real_right;
			}
			
			while (left < open) {
				pref_set.erase(make_pair(prefs[left], left));
				suff_set.erase(make_pair(suffs[left], left));
				++left;
			}
			
			while (right > close) {
				pref_set.erase(make_pair(prefs[right], right));
				suff_set.erase(make_pair(suffs[right], right));
				pref_sum += a[right - 1];
				--right;
			}
			
			//cerr << real_left << " " << left << " " << right << endl;
		} else {
			int first_close = -1, last_close = -1;
			bool found = false;
			int balance = 0;
			while (closes.size() > 0) {
				int close = closes.front();
				closes.pop_front();
				
				balance += close - last_close - 1;
				if (balance >= 0) { first_close = -1; balance = 0; }
				
				if (first_close == -1) first_close = close;
				last_close = close;
				--balance;
				
				if (pref_sum + (prefs[close] - prefs[left - 1]) < 0) {
					found = true;
					break;
				}
			}
			
			if (!found) break;
			
			int first_open = -1, last_open = n + 1;
			balance = 0;
			while (opens.size() > 0) {
				int open = opens.back();
				opens.pop_back();
				
				balance -= (last_open - open - 1);
				if (balance <= 0) { first_open = -1; balance = 0; }
				
				if (first_open == -1) { first_open = open; }
				last_open = open;
				
				//cout << balance << " " << first_open << endl;
				
				++balance;
				
				if (pref_sum + (prefs[open - 1] - prefs[left - 1]) < 0) {
					break;
				}
			}
			
			int open = first_open;
			int close = first_close;
			
			//cerr << real_left << " " << real_right << " " << open << " " << close << " " << left << " " << right << "\n";
			ans.emplace_back(real_left + (close - left) + 1, real_left + (open - left) + 1);
			
			while (opens.size() > 0 && opens.front() < close) {
				opens.pop_front();
				//++real_left;
			}
			
			real_left += close - left;
			
			while (closes.size() > 0 && closes.back() > open) {
				closes.pop_back();
			}
			
			while (left < close) {
				pref_set.erase(make_pair(prefs[left], left));
				suff_set.erase(make_pair(suffs[left], left));
				pref_sum += a[left - 1];
				++left;
			}
			
			while (right > open) {
				pref_set.erase(make_pair(prefs[right], right));
				suff_set.erase(make_pair(suffs[right], right));
				--right;
			}
			
			//cerr << real_left << " " << left << " " << right << endl;
		}
		
		inverted = !inverted;
	}
	
	return ans;
}

vector<ii> get_brute_answer(int n, vector<int> a) {
	
	
	queue<vi> q;
	q.push(a);
	
	map<vi, int> d;
	d[a] = 0;
	
	map<vi, ii> p;
	p[a] = make_pair(-1, -1);
	
	vi finish(0);
	
	while (q.size() > 0) {
		vi from = q.front();
		q.pop();
		
		/*
		cout << "from: " << endl;
		for (int v : from) cout << (v == 1 ? "(" : ")");
		cout << endl;
		*/
		
		int pref = 0;
		for (int i = 0; i < n; ++i) {
			pref += from[i];
			if (pref < 0) break;
		}
		
		if (pref >= 0) {
			finish = from;
			break;
		}
		
		for (int left = 0; left < n; ++left){ 
			for (int right = left + 2; right <= n; ++right) {
				vi to = from;
				reverse(to.begin() + left, to.begin() + right);
				
				/*
				cout << "to: " << endl;
				for (int v : to) cout << (v == 1 ? "(" : ")");
				cout << endl;
				*/
				
				if (d.find(to) != d.end()) continue;
				
				
				
				d[to] = d[from] + 1;
				p[to] = make_pair(left, right);
				q.push(to);
			}
		}
	}
	
	vector<ii> ans;
	while (p[finish].first != -1) {
		auto& [left, right] = p[finish];
		ans.emplace_back(left + 1, right);
		reverse(finish.begin() + left, finish.begin() + right);
	}
	
	return ans;
}

#define STRESS

#ifdef STRESS

typedef uniform_int_distribution<> uid;
typedef mt19937 rnd_t;

void stress() {
	ll seed = 12345;
	bool with_time = true;
	if (with_time) seed += time(0);
	rnd_t rnd(seed);
	
	uid nGen(1, 10);
	//uid aGen(0, 999);
	
	for (int it = 0; it < 10000; ++it) {
		int n = nGen(rnd);
		
		vi a(n + n);
		for (int i = 0; i < n; ++i) {
			a[i] = 1;
			a[i + n] = -1;
		}
		
		for (int i = 1; i < 2 * n; ++i) {
			uid vGen(0, i);
			
			int nxt = vGen(rnd);
			swap(a[i], a[nxt]);
		}
		
		/*cout << n << endl;
		for (int v : a) cout << (v == 1 ? "(" : ")");
		cout << endl;*/
		
		//cout << "expected started" << endl;
		
		auto expected = get_brute_answer(n * 2, a);
		
		/*cout << n << endl;
			for (int v : a) cout << (v == 1 ? "(" : ")");
			cout << endl;*/
			
			//cout << "actual started" << endl;
		
		auto actual = get_answer(n * 2, a);
		
		auto print_ans = [&](vector<ii> ans) {
			cout << ans.size() << "\n";
			for (auto& [left, right] : ans) {
				cout << left << " " << right << "\n";
			}
		};
		
		if (expected.size() != actual.size()) {
			cout << "GOTCHA !!!" << endl;
			
			cout << n << "\n";
			for (int v : a) cout << (v == 1 ? "(" : ")");
			cout << "\n";
			
			cout << "===" << endl;
			print_ans(expected);
			print_ans(actual);
			cout << "===" << endl;
			
			break;
		}
	}
}

#endif


void solve_test() {
	int n = ri() * 2;
	string s = rs();
	
	vi a(n, 0);
	for (int i = 0; i < n; ++i) {
		if (s[i] == '(') a[i] = 1;
		else a[i] = -1;
	}
	
	vector<ii> ans = get_answer(n, a);
	cout << ans.size() << "\n";
	for (auto& [left, right] : ans) {
		if (left > right) swap(left, right);
		cout << left << " " << right << "\n";
	}
}

void solve() {
	int t = ri();
	while (t --> 0) {
		solve_test();
	}	
}

int main() {
    init_io();
    #ifdef STRESS
    stress();
    #else
    solve();
    #endif
    return 0;
}
