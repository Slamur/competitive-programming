#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

template <typename T>
class SegmentTree {
private:
	
	int size;
	T neutral;
	vector<T> tree;

	void set(int v, T value) {
		tree[v] = value;
	}
	
	void clear(int v) {
		set(v, neutral);
	}
	
	void accumulate(int v_to, int v_from) {
		tree[v_to] += tree[v_from];
	}
	
	void update_vertex(int v, int v_left, int v_right) {
		clear(v);
		accumulate(v, v_left);
		accumulate(v, v_right);
	}
	
	vector<T> array;
	void build_tree(int v, int left, int right) {
		if (left + 1 == right) {
			set(v, array[left]);
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			build_tree(v_left, left, mid);
			build_tree(v_right, mid, right);
			update_vertex(v, v_left, v_right);
		}
	}
	
	const int v_res = 0;
	int start, end;
	void get_tree(int v, int left, int right) {
		if (start <= left && right <= end) {
			accumulate(v_res, v);
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			if (start < mid) get_tree(v_left, left, mid);
			if (mid < end) get_tree(v_right, mid, right);
		}
	}
	
	int index;
	void update_tree(int v, int left, int right) {
		if (left + 1 == right) {
			accumulate(v, v_res);
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			if (index < mid) update_tree(v_left, left, mid);
			else update_tree(v_right, mid, right);
			update_vertex(v, v_left, v_right);
		}
	}
	
public:
	
	SegmentTree(int n, const T& _neutral)
	: size(n)
	, neutral(_neutral)
	, tree(size << 2, neutral) {
		
	}
	
	void build(const vector<T>& _array) {
		array = _array;
		build_tree(1, 0, size);
	}
	
	T get(int _start, int _end) {
		start = _start;
		end = _end + 1;
		
		clear(v_res);
		get_tree(1, 0, size);
		return tree[v_res];
	}
	
	void update(int _index, T value) {
		index = _index;
		set(v_res, value);
		update_tree(1, 0, size);
	}
};

struct query_t {
	int index;
	int start, end;
	
	query_t(int _index, int _start, int _end)
	: index(_index)
	, start(_start)
	, end(_end)
	{} 
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	const int max_x = 1e6 + 1;
	
	int n, m;
	cin >> n >> m;
	
	vector<pair<int, int>> segs(n);
	for (auto& [s, e] : segs) {
		cin >> s >> e;
	}
	
	vector<vector<int>> points(m);
	for (auto& xs : points) {
		int size;
		cin >> size;
		
		xs.resize(size);
		for (int& x : xs) cin >> x;
		xs.push_back(max_x);
	}
	
	vector<vector<int>> ends(max_x);
	for (auto& [s, e] : segs) {
		ends[s].push_back(e);
	}
	
	vector<vector<query_t>> queries(max_x);
	for (int i = 0; i < m; ++i) {
		auto& xs = points[i];
		for (int j = 0; j + 1 < xs.size(); ++j) {
			queries[xs[j]].emplace_back(i, xs[j], xs[j + 1] - 1);
		}
	}
	
	vector<int> answers(m, 0);
	
	SegmentTree<int> tree(max_x, 0);
	for (int x = 0; x < max_x; ++x) {
		for (int end : ends[x]) {
			tree.update(end, 1);
		}
		
		for (auto& query : queries[x]) {
			answers[query.index] += tree.get(query.start, query.end);
		}
	}
	
	for (int ans : answers) {
		cout << ans << "\n";
	}
	
	return 0;
}