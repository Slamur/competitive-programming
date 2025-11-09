#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> a(n, std::vector<int>(n, 0));
    for (auto& row : a) {
        for (auto& val : row) std::cin >> val;
    }

    auto get_ans = [&]() {
        const int max_bit = 27;

        std::vector<std::vector<bool>> prev_good(n + 1, std::vector<bool>(n + 1, true));
        std::vector<std::vector<bool>> cur_good(n + 1, std::vector<bool>(n + 1, true));

        auto get_bit = [&](int mask, int bit) {
            return (mask >> bit) & 1;
        };

        int ans = 0;
        for (int bit = max_bit; bit >= 0; --bit) {

            for (int x = 0; x < n; ++x) {
                for (int y = 0; y < n; ++y) {
                    bool v_good = get_bit(a[x][y], bit);
                    cur_good[x + 1][y + 1] = v_good && prev_good[x + 1][y + 1] && (cur_good[x][y + 1] || cur_good[x + 1][y]);
                }
            }

            if (cur_good[n][n]) {
                ans |= (1 << bit);

                for (int x = 0; x < n; ++x) {
                    for (int y = 0; y < n; ++y) {
                        prev_good[x + 1][y + 1] = cur_good[x + 1][y + 1];
                    }
                }
            }
        }

        return ans;
    };

    auto ans = get_ans();
    std::cout << ans << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
