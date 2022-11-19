#include <bits/stdc++.h>

using namespace std;

void solve_test() {
    int n;
    cin >> n;
    
    vector<int> b(n / 2);
    for (auto& v : b) cin >> v;
    
    auto get_ans = [&]() {
        vector<int> no_ans = { -1 };
        
        set<int> b_tree(b.begin(), b.end());
        if (b_tree.size() != b.size()) return no_ans;
        
        set<int, greater<int>> free;
        for (int i = 1; i <= n; ++i) free.insert(i);
        for (int v : b) free.erase(v);
        
        vector<int> p;
        
        reverse(b.begin(), b.end());
        for (int v : b) {
            auto it = free.upper_bound(v);
            if (it == free.end()) {
                return no_ans;
            }
            
            p.push_back(v);
            p.push_back(*it);
            free.erase(it);
        }
        
        reverse(p.begin(), p.end());
        return p;
    };
    
    auto ans = get_ans();
    for (auto& v : ans) cout << v << " ";
    cout << "\n";
}

int main() {
    int t;
    cin >> t;
    
    while (t --> 0) {
        solve_test();
    }
    
    return 0;
}
