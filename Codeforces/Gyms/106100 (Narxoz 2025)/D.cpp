// Combination of the author and DNA solutions

#include <bits/stdc++.h>

using ll = int64_t;

size_t none_node = SIZE_MAX;

using node_t = struct Node {
    ll sum = 0;
    size_t left = none_node;
    size_t right = none_node;
};

constexpr int MAX_Q = 1e5 * 2;

node_t nodes[MAX_Q * 20];
size_t node_cnt = 0;

size_t create_node(const ll sum, const size_t left, const size_t right) {
    nodes[node_cnt].sum = sum;
    nodes[node_cnt].left = left;
    nodes[node_cnt].right = right;

    return node_cnt++;
}

size_t create_empty() {
    return create_node(0, none_node, none_node);
}

size_t get_left(const size_t v) {
    auto& left = nodes[v].left;

    if (left == none_node) {
        left = create_node(0, none_node, none_node);
    }

    return left;
}

size_t get_right(const size_t v) {
    auto& right = nodes[v].right;

    if (right == none_node) {
        right = create_node(0, none_node, none_node);
    }

    return right;
}

class PersistentSegmentTree {

    size_t roots[MAX_Q + 1];
    size_t last_version = 0;

    size_t _size;

    size_t _pos;
    int _delta;

    size_t _update_tree(const size_t v, const size_t left, const size_t right) {
        if (left + 1 == right) {
            return create_node(nodes[v].sum + _delta, none_node, none_node);
        }

        size_t mid = (left + right) / 2;
        if (_pos < mid) {
            size_t new_left = _update_tree(get_left(v), left, mid);
            return create_node(
                nodes[v].sum + _delta,
                new_left,
                nodes[v].right
            );
        } else {
            size_t new_right = _update_tree(get_right(v), mid, right);
            return create_node(
                nodes[v].sum + _delta,
                nodes[v].left,
                new_right
            );
        }
    }

    size_t _start, _end;
    node_t _result;

    void _get_tree(const size_t v, const size_t left, const size_t right) {
        if (v == none_node) return;

        const auto& node = nodes[v];

        if (_start <= left && right <= _end) {
            _result.sum += node.sum;
            return;
        }

        const size_t mid = (left + right) / 2;
        if (_start < mid) _get_tree(node.left, left, mid);
        if (mid < _end) _get_tree(node.right, mid, right);
    }

public:
    explicit PersistentSegmentTree(const size_t n)
    : _size(n) {
        last_version = 0;
        roots[last_version] = create_empty();
    }

    size_t update_last(size_t pos, int delta) {
        _pos = pos;
        _delta = delta;

        roots[last_version + 1] = _update_tree(roots[last_version], 0, _size);
        ++last_version;

        return last_version;
    }

    ll get_range(const size_t version, const size_t start, const size_t end) {
        _start = start;
        _end = end + 1;

        _result.sum = 0;

        _get_tree(roots[version], 0, _size);

        return _result.sum;
    }
};

void solve() {
    size_t n, q;
    std::cin >> n >> q;

    std::vector<size_t> a(n);
    for (auto& v : a) {
        std::cin >> v;
    }

    constexpr int mod = 1e9 + 9;

    std::mt19937_64 rnd64(std::chrono::system_clock::now().time_since_epoch().count());

    constexpr int none_id = -1;
    std::vector ids(n + 1, none_id);
    for (const auto& v : a) {
        auto& id = ids[v];
        if (id != none_id) continue;

        id = rnd64() % mod;
    }

    std::vector<ll> prefix_sums(n + 1, 0);
    for (size_t i = 0; i < n; ++i) {
        prefix_sums[i + 1] = prefix_sums[i] + ids[a[i]];
    }

    std::vector<std::vector<size_t>> positions(n + 1);
    for (size_t i = 0; i < n; ++i) {
        positions[a[i]].push_back(i);
    }

    auto get_cnt = [&](const size_t value, const size_t left, const size_t right) {
        const auto& pos = positions[value];
        const auto it1 = std::lower_bound(pos.begin(), pos.end(), left);
        const auto it2 = std::upper_bound(pos.begin(), pos.end(), right);

        return std::distance(it1, it2);
    };

    PersistentSegmentTree tree(n);

    std::vector<size_t> versions(n);

    constexpr size_t none_pos = SIZE_MAX;
    std::vector last(n + 1, none_node);
    for (size_t i = 0; i < n; ++i) {
        const auto& value = a[i];
        const auto& id = ids[value];

        const auto& last_pos = last[value];

        if (last_pos != none_pos) tree.update_last(last_pos, -id);
        versions[i] = tree.update_last(i, id);

        last[value] = i;
    }

    constexpr size_t block_size = 5;
    for (size_t it = 1; it <= q; ++it) {
        size_t left, right;
        std::cin >> left >> right;

        --left, --right;

        const size_t expected_cnt = get_cnt(a[left], left, right);
        const ll range_sum = prefix_sums[right + 1] - prefix_sums[left];
        const ll unique_sum = tree.get_range(versions[right], left, right);

        bool good = (unique_sum * expected_cnt == range_sum);

        std::cout << (good ? "YES" : "NO") << "\n";

        if (it % block_size == 0) {
            std::cout.flush();
        }
    }

    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
