// I wrote a huge stress for this problem and decided to keep it (commented parts)

#include <bits/stdc++.h>

int64_t get_ans(int n, std::vector<int> a, int b_size, std::vector<int> b) {
    std::unordered_map<int, std::vector<int>> a_pos;
    for (int i = 0; i < n; ++i) {
        a_pos[a[i]].push_back(i);
    }

    std::vector<int> pointers(b_size, -1);

    std::vector<int> block_starts(n, -1);
    for (int i = 0; i < n; ++i) {
        if (i == 0 || a[i] != a[i - 1]) block_starts[i] = i;
        else block_starts[i] = block_starts[i - 1];
    }

    auto jump_to = [&](int bj, int end) {
        int bv = b[bj];

        auto bv_pos_it = a_pos.find(bv);
        if (bv_pos_it == a_pos.end()) {
            return -1;
        }

        auto bv_pos = bv_pos_it->second;

        int& pointer = pointers[bj];
        while (pointer + 1 < bv_pos.size() && bv_pos[pointer + 1] < end) {
            pointer++;
        }

        if (pointer < 0) return -1;
        return bv_pos[pointer];
    };

    int64_t ans = 0;

    int last_b_block_size = 1;
    for (int bj = b_size - 2; bj >= 0; --bj) {
        if (b[bj] == b.back()) ++last_b_block_size;
        else break;
    }

    for (int end = 0; end < n; ++end) {
        if (a[end] != b.back()) continue;

        int start = end;
        for (int bj = b_size - 2; bj >= 0 && start >= 0; --bj) {
            start = jump_to(bj, start);
        }

        if (start < 0) continue;

        if (block_starts[start] == block_starts[end]) {
            // all b[i] are equal, a[l..r] are all equal
            if (start != block_starts[start]) {
                ans += 1;
                continue;
            }
        }

        int end_block_start = block_starts[end];
        int last_a_block_size = end - end_block_start + 1;
        if (last_a_block_size > last_b_block_size) {
            continue;
        }

        ans += (start + 1);
    }

    return ans;
}

/*
int64_t get_brute_ans(int n, std::vector<int> a, int b_size, std::vector<int> b) {
    int64_t ans = 0;

    auto check = [&](int start, int end) {
        bool was_other = false;

        int  j = b_size - 1;
        for (int i = end; i >= start; --i) {
            was_other |= a[i] != a[end];
            if (j < 0 || a[i] != b[j]) {
                if (!was_other) return false;
            } else {
                --j;
            }
        }

        return j < 0;
    };

    for (int start = 0; start < n; ++start) {
        for (int end = start; end < n; ++end) {
            if (check(start, end)) ++ans;
        }
    }

    return ans;
}
*/

void solve() {
    int n, b_size;
    std::cin >> n >> b_size;

    std::vector<int> a(n), b(b_size);
    for (auto& v : a) std::cin >> v;
    for (auto& v : b) std::cin >> v;

    auto ans = get_ans(n, a, b_size, b);

/*
#ifndef ONLINE_JUDGE
    auto ans_brute = get_brute_ans(n, a, b_size, b);
    if (ans_brute != ans) {
        std::cout << "GOTCHA!" << std::endl;
    }
#endif
*/

    std::cout << ans << std::endl;
}

/*
void stress() {
    int magic = 100;

    int n = 1000;
    int b_size = 100;

    std::mt19937 rnd(5648947);

    std::uniform_int_distribution<int> gen_val(1, 1e9);

    for (int it = 0; it < magic; ++it) {
        std::vector<int> a(n);
        for (int& v : a) v = gen_val(rnd);

        std::vector<int> b(b_size);

        std::uniform_int_distribution<int> gen_p(0, n - 1);

        std::vector<int> bp;
        for (int j = 0; bp.size() < b_size; ++j) {
            int p = gen_p(rnd);
            if (std::find(bp.begin(), bp.end(), p) != bp.end()) continue;

            bp.push_back(p);
        }

        std::sort(bp.begin(), bp.end());
        for (int i = 0; i < b_size; ++i) {
            b[i] = a[bp[i]];
        }


        auto ans = get_ans(n, a, b_size, b);
        auto ans_brute = get_brute_ans(n, a, b_size, b);

        if (ans != ans_brute) {
            std::cout << "GOTCHA!" << std::endl;
            std::cout << ans << " " << ans_brute << std::endl;
            std::cout << "===========================" << std::endl;
            std::cout << n << " " << b_size << std::endl;
            for (int& v : a) std::cout << v << " ";
            std::cout << std::endl;
            for (int& v : b) std::cout << v << " ";
            std::cout << std::endl;

            break;
        }
    }
}
*/

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
    //stress();

    return 0;
}
