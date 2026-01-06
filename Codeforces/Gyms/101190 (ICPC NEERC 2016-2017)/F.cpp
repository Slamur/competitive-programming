#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;
using vll = vector<ll>;

void init_io(const string& filename) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	if (filename.size() > 0) {
	    freopen((filename + ".in").c_str(), "rt", stdin);
	    freopen((filename + ".out").c_str(), "wt", stdout);   
	}
	
	cout << setprecision(10) << fixed;
}

void solve() {
	string s;
	cin >> s;
	
	reverse(s.begin(), s.end());
	
	int n = s.size();
	
	string types = "CW";
	vector<int> a(1, 0);
	
	for (auto& ch : s) {
		int v = types.find(ch);
		a.push_back(v);
	}
	
	vector<vll> prefs(2, vll(n + 1, 0));
	
	for (int i = 1; i <= n; ++i) {
		for (int t = 0; t < types.size(); ++t) {
			prefs[t][i] = prefs[t][i - 1];
		}
		
		prefs[a[i]][i] += i;
	}
	
	vector<long double> dp(n + 1, 0.0);
	vector<long double> pref_dp(n + 1, 0.0);
	for (int i = 1; i <= n; ++i) {
		dp[i] = pref_dp[i - 1] + prefs[1 - a[i]][i - 1];
		dp[i] /= i;
		pref_dp[i] = pref_dp[i - 1] + dp[i];
	}
	
	cout << dp[n] << endl;
}

int main() {
	init_io("foreign");
    	solve();
	
	return 0;
}
