#include <bits/stdc++.h>

const int MAX_N = 500, MAX_B_SIZE = 500;

int dp[MAX_N + 1][MAX_B_SIZE + 1][MAX_N + 1];

std::vector<int> get_ans(int n, std::string a, int b_size, std::string b) {
    std::vector<std::vector<int>> b_next(2, std::vector<int>(n + 1, 0));

    for (int bi = 0; bi <= b_size; ++bi) {
            std::vector<int> inc_codes;
            if (bi < b_size) {
                int val_code = b[bi] - '0';
                b_next[val_code][bi] = bi + 1;

                inc_codes = { 1 - val_code };
            } else {
                inc_codes = { 0, 1 };
            }

        for (int inc_code : inc_codes) {
            std::string pref = b.substr(0, bi);
            pref.push_back((char)(inc_code + '0'));

            for (int size = bi; size > 0; --size) {
                std::string suff = pref.substr(pref.size() - size, size);
                if (suff == pref.substr(0, size)) {
                    b_next[inc_code][bi] = suff.size();
                    break;
                }
            }
        }
    }

    int inf = n + 1;
    for (int i = 0; i <= n; ++i) {
        for (int bi = 0; bi <= b_size; ++bi) {
            for (int k = 0; k <= n; ++k) {
                dp[i][bi][k] = inf;
            }
        }
    }

    for (int bi = 0; bi < b_size; ++bi) {
        dp[0][0][0] = 0;
    }


    for (int i = 0; i < n; ++i) {
        for (int bi = 0; bi <= b_size; ++bi) {
            for (int k = 0; k <= n; ++k) {
                for (int code = 0; code < 2; ++code) {
                    int delta = (code != (a[i] - '0'));

                    int next_bi = b_next[code][bi];
                    int next_full = (next_bi == b_size);
                    dp[i + 1][next_bi][k + next_full] = std::min(dp[i + 1][next_bi][k + next_full], dp[i][bi][k] + delta);
                }
            }
        }
    }

    std::vector<int> ans(n - b_size + 2, inf);

    for (int k = 0; k < ans.size(); ++k) {
        for (int bi = 0; bi <= b_size; ++bi) {
            ans[k] = std::min(ans[k], dp[n][bi][k]);
        }
    }

    for (int& v : ans) {
        if (v == inf) v = -1;
    }

    return ans;
}

void solve() {
    int n, b_size;
    std::cin >> n >> b_size;

    std::string a, b;
    std::cin >> a;
    std::cin >> b;

    auto ans = get_ans(n, a, b_size, b);

    for (int v : ans) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
