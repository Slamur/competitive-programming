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
	
	vector<vi> prefs(2, vi(n + 1, 0));
	vector<vll> sum_prefs(2, vll(n + 1, 0));
	
	for (int i = 1; i <= n; ++i) {
		for (int t = 0; t < types.size(); ++t) {
			prefs[t][i] = prefs[t][i - 1];
		}
		
		prefs[a[i]][i]++;
		
		for (int t = 0; t < types.size(); ++t) {
			sum_prefs[t][i] = sum_prefs[t][i - 1] + prefs[t][i];
		}
	}
	
	vector<long double> dp(n + 1, 0.0);
	vector<long double> pref_dp_minus_i(n + 1, 0.0);
	for (int i = 1; i <= n; ++i) {
		dp[i] = pref_dp_minus_i[i - 1];
		dp[i] += sum_prefs[a[i]][i - 1];
		dp[i] /= i;
		
		dp[i] += (i - prefs[a[i]][i]);
		
		pref_dp_minus_i[i] += pref_dp_minus_i[i - 1];
		pref_dp_minus_i[i] += dp[i] - i;
	}
	
	cout << dp[n] << endl;
}

int main() {
	init_io("foreign");
    	solve();
	
	return 0;
}
