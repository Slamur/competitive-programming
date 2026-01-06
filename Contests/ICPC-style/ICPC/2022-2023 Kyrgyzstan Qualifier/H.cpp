#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    
    int mod = 1000 * 1000 + 7;
    
    vector<int> dp(b + 1, 0);
    vector<bool> can(b + 1, false);
    dp[a] = 1;
    can[a] = true;
    
    for (int i = a, lim = b / y; i < b; ++i) {
        if (i + x <= b) {
            int j = i + x;
            dp[j] += dp[i];
            can[j] = can[j] | can[i];
            if (dp[j] > mod) dp[j] -= mod;
        }
        
        if (i <= lim) {
            int j = i * y;
            dp[j] += dp[i];
            can[j] = can[j] | can[i];
            if (dp[j] > mod) dp[j] -= mod;
        }
    }
    
    int ans = can[b] ? dp[b] : -1;
    cout << ans << "\n";
    
    return 0;
}
