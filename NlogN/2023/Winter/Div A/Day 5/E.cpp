#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;
using ii = pair<int, int>;
using vll = vector<ll>;

void solve_test() {
    int n, x;
    cin >> n >> x;
    
    vi c(n);
    for (auto& v : c) cin >> v;
    
    vi t(n - 1);
    for (auto& v : t) cin >> v;
    
    auto get_ans = [&]() {
    	vll pref_t(n + 1, 0);
    	for (int i = 1; i < n; ++i) {
    		pref_t[i + 1] = pref_t[i] + t[i - 1];
    	}
    	
    	vll pref_c(n + 1, 0);
    	for (int i = 0; i < n; ++i) {
    		pref_c[i + 1] = pref_c[i] + c[i];
    	}
    
    	auto can = [&](ll max_time) {
    		vll dp(n + 1, x + 1);
    		dp[0] = 0;
    		
    		for (int i = 1; i <= n; ++i) {
    			for (int j = i - 1; j >= 0; --j) {		
	    			// max_time >= max(t[k..i] + ceil(c[(j + 1)..k] / prod[i,k]))
	    			// max_time - t[k..i] >= ceil(c[(j + 1)..k] / prod)
	    			// prod >= c[(j + 1..k)] / (max_time - t[k..i])
	    			
	    			ll max_prod = 0;
	    			for (int k = i; k > j; --k) {
	    				ll q_time = max_time - (pref_t[i] - pref_t[k]);
	    				if (q_time < 0) {
	    					max_prod = x + 1;
	    					break;
	    				}
	    				
	    				ll all_c = pref_c[k] - pref_c[j];
	    				if (all_c == 0) break;
	    				
	    				if (q_time == 0) {
	    					if (all_c > 0) max_prod = x + 1;
	    					break;
	    				}
	    				
	    				ll prod = max(ll(1), all_c / q_time);
	    				while ((all_c + prod - 1) / prod > q_time) ++prod;
	    				
	    				max_prod = max(max_prod, prod);
	    			}
	    			
	    			dp[i] = min(dp[i], dp[j] + max_prod);
	    		}
    		}
    		
    		return dp[n] <= x;
    	};
    
    	ll left = -1, right = 8e18;
    	while (right - left > 1) {
    		ll mid = (left + right) / 2;
    		if (can(mid)) right = mid;
    		else left = mid;
    	}
    	
    	return right;
    };
    
    auto ans = get_ans();
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 	  
	  int t;
	  cin >> t;
	
	  while (t --> 0) {
	      solve_test();
    }
    
    return 0;
}
