#include <bits/stdc++.h>

using ll = int64_t;

void solve_test() {
    size_t n;
    std::cin >> n;

    using op_t = std::tuple<bool, bool>; // is_set, is_true

    std::vector<op_t> ops(n);
    for (auto& [is_set, is_true] : ops) {
        std::string op_type, value;
        std::cin >> op_type >> value;

        is_set = (op_type == "set");
        is_true = (value == "true");
    }

    size_t edges_cnt;
    std::cin >> edges_cnt;

    std::vector<std::vector<size_t>> graph(n);
    for (size_t e = 0; e < edges_cnt; ++e) {
        size_t v_before, v_after;
        std::cin >> v_before >> v_after;
        --v_before, --v_after;

        graph[v_before].push_back(v_after);
    }

    auto get_ans = [&]() {
        std::vector<size_t> no_ans(0);

        std::vector<size_t> false_sets, false_unsets;

        size_t none = n;
        size_t true_set = none, true_unset = none;

        for (size_t v = 0; v < n; ++v) {
            auto& [is_set, is_true] = ops[v];

            if (is_true) {
                if (is_set) {
                    true_set = v;
                } else {
                    true_unset = v;
                }
            } else {
                if (is_set) {
                    false_sets.push_back(v);
                } else {
                    false_unsets.push_back(v);
                }
            }
        }

        auto has_cycle = [&](std::vector<size_t>& order) {
            std::vector<bool> used(n, false);

            for (auto& v : order) {
                for (auto& to : graph[v]) {
                    if (!used[to]) return true;
                }

                used[v] = true;
            }

            return false;
        };

        auto top_sort = [&]() {
            std::vector<size_t> order;

            std::vector<bool> visited(n, false);
            std::function<void(size_t)> dfs = [&](size_t v) {
                if (visited[v]) return;

                visited[v] = true;

                for (auto& to : graph[v]) {
                    dfs(to);
                }

                order.push_back(v);
            };

            for (size_t v = 0; v < n; ++v) {
                dfs(v);
            }

            if (has_cycle(order)) {
                return no_ans;
            }

            std::reverse(order.begin(), order.end());
            return order;
        };

        if (true_set == none && true_unset == none) {
            if (!false_sets.empty()) {
                return no_ans;
            }

            return top_sort();
        }

        if (true_set == none && true_unset != none) {
            return no_ans;
        }

        // always if true_set
        for (auto& false_set : false_sets) {
            graph[true_set].push_back(false_set);
        }

        if (true_unset == none) {
            for (auto false_unset : false_unsets) {
                graph[false_unset].push_back(true_set);
            }

            return top_sort();
        }

        if (true_unset != none) {
            graph[true_set].push_back(true_unset);

            for (auto& false_set : false_sets) {
                graph[false_set].push_back(true_unset);
            }
        }

        if (true_unset != none) {
            std::vector<bool> visited(n, false);
            std::queue<size_t> q;

            auto push = [&](size_t v) {
                q.push(v);
                visited[v] = true;
            };

            push(true_set), push(true_unset);
            for (auto& false_set : false_sets) {
                push(false_set);
            }

            while (!q.empty()) {
                size_t v = q.front();
                q.pop();

                for (auto to : graph[v]) {
                    if (visited[to]) continue;
                    push(to);
                }
            }

            for (auto& false_unset : false_unsets) {
                if (visited[false_unset]) {
                    graph[true_unset].push_back(false_unset);
                } else {
                    graph[false_unset].push_back(true_set);
                }
            }

            return top_sort();
        }

        // impossible
        return no_ans;
    };

    auto ans = get_ans();
    if (ans.empty()) {
        std::cout << -1 << std::endl;
    } else {
        for (auto& v : ans) {
            std::cout << v + 1 << " ";
        }
        std::cout << std::endl;
    }
}

void solve() {
    int t = 1;
    // std::cin >> t;

    while (t --> 0) {
        solve_test();
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}