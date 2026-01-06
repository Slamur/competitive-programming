#include <bits/stdc++.h>

using ll = int64_t;

using query_t = std::tuple<int, int, ll>;

const int update_type = 1, connect_type = 2, ask_type = 3;

struct DSU {
    using info_t = std::pair<ll, int>; // parent, size
    std::unordered_map<ll, info_t> info;

    using change_t = std::tuple<int, ll, info_t>; // revision, color, old_info

    int cur_revision;

    DSU() {
        cur_revision = 0;
    }

    info_t get_info(ll x) {
        auto it = info.find(x);
        if (it != info.end()) {
            return it->second;
        }

        auto res = std::make_pair(x, 1);
        info[x] = res;
        return res;
    }

    std::vector<change_t> changes;

    void begin() {
        ++cur_revision;
    }

    void end() {
        while (changes.size() > 0) {
            auto [revision, color, old_info] = changes.back();
            if (revision != cur_revision) break;

            changes.pop_back();

            info[color] = old_info;
        }

        --cur_revision;
    }

    int get(ll x) {
        auto info = get_info(x);
        if (info.first == x) return x;

        return get(info.first);
    }

    void merge(ll a, ll b) {
        a = get(a), b = get(b);

        if (a == b) return;

        auto old_a_info = get_info(a);
        auto old_b_info = get_info(b);

        if (old_a_info.second < old_b_info.second) {
            std::swap(a, b);
            std::swap(old_a_info, old_b_info);
        }

        changes.emplace_back(cur_revision, b, old_b_info);
        info[b] = std::make_pair(a, old_b_info.second);

        changes.emplace_back(cur_revision, a, old_a_info);
        info[a] = std::make_pair(a, old_a_info.second + old_b_info.second);
    }

    bool connected(ll a, ll b) {
        return get(a) == get(b);
    }
};


using edge_t = std::pair<ll, ll>;
struct SegmentTree {


    int size;
    std::vector<std::vector<edge_t>> t;

    SegmentTree(int n)
    : size(n)
    , t(n << 2) {

    }

    int _start, _end;
    edge_t _val;

    void update_tree(int v, int left, int right) {
        if (_start <= left && right <= _end) {
            t[v].push_back(_val);
        } else {
            int mid = (left + right) / 2;
            int vl = (v << 1), vr = vl + 1;

            if (_start < mid) update_tree(vl, left, mid);
            if (mid < _end) update_tree(vr, mid, right);
        }
    }

    void update(int start, int end, edge_t edge) {
        // [start, end)

        _start = start;
        _end = end;
        _val = edge;

        if (start >= end) return;

        update_tree(1, 0, size);
    };

    std::vector<bool> ans;

    std::vector<edge_t> _queries;
    DSU _dsu;

    void get(std::vector<edge_t> queries) {
        _queries = queries;
        _dsu = DSU();

        get_tree(1, 0, size);
    }

    void get_tree(int v, int left, int right) {
        _dsu.begin();
        for (auto& [f, s] : t[v]) {
            _dsu.merge(f, s);
        }

        if (left + 1 == right) {
            if (left < _queries.size()) {
                auto [f, s] = _queries[left];
                if (f != -1) {
                    ans.push_back(_dsu.connected(f, s));
                }
            }
        } else {
            int mid = (left + right) / 2;
            int vl = (v << 1), vr = vl + 1;

            get_tree(vl, left, mid);
            get_tree(vr, mid, right);
        }

        _dsu.end();
    }
};

std::vector<bool> get_ans(int n, std::vector<ll> t, int q, std::vector<query_t> queries) {
    std::vector<bool> ans;

    const int tree_size = q + 1;
    SegmentTree tree(tree_size);

    std::vector<bool> to_next(n, false);
    std::map<edge_t, std::pair<int, int>> edges;

    auto get_edge = [&](int f, int s) {
        int tf = t[f], ts = t[s];
        if (tf > ts) {
            std::swap(tf, ts);
        }

        return edge_t{tf, ts};
    };

    auto update = [&](int f, int s, int delta, int time) {
        if (t[f] == t[s]) return;

        auto fs = get_edge(f, s);

        edges[fs].first += delta;

        if (delta > 0 && edges[fs].first == delta) {
            edges[fs].second = time;
        }

        if (delta < 0 && edges[fs].first == 0) {
            tree.update(edges[fs].second, time, fs);
        }
    };

    std::vector<edge_t> ask_queries(q, std::make_pair(-1, -1));
    for (int i = 0; i < q; ++i) {
        auto& [type, f, s] = queries[i];

        if (connect_type == type) {
            to_next[f] = true;

            update(f, s, 1, i);
        }

        if (update_type == type) {
            int nf = (f + 1) % n;
            int pf = (f + n - 1) % n;
            if (to_next[f]) {
                update(f, nf, -1, i);
            }

            if (to_next[pf]) {
                update(pf, f, -1, i);
            }

            t[f] = s;

            if (to_next[f]) {
                update(f, nf, 1, i);
            }

            if (to_next[pf]) {
                update(pf, f, 1, i);
            }
        }

        if (ask_type == type) {
            auto edge = get_edge(f, s);
            ask_queries[i] = edge;
        }
    }

    for (auto [edge, info]: edges) {
        if (info.first > 0) {
            tree.update(info.second, q, edge);
        }
    }

    tree.get(ask_queries);

    return tree.ans;
}

void solve() {
    int n, q;
    std::cin >> n >> q;

    std::vector<ll> t_start(n, 0);
    for (auto& v : t_start) std::cin >> v;

    std::vector<query_t> queries(q);
    for (auto& [type, f, s] : queries) {
        std::cin >> type;
        if (update_type == type) {
            std::cin >> f >> s;
        }
        if (connect_type == type) {
            std::cin >> f;
            s = (f + 1) % n;
        }
        if (ask_type == type) {
            std::cin >> f >> s;
        }
    }

    auto ans = get_ans(n, t_start, q, queries);

    for (auto v : ans) {
        std::cout << (v ? "YES" : "NO") << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
