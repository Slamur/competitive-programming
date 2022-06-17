#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

template <typename T>
class SegmentTree {
private:
	
	int size;
	T inf;
	vector<vector<T>> tree;

	void clear_vertex(int v) {
		tree[v].clear();
	}
	
	void update_vertex(int v, int v_left, int v_right) {
		auto& tl = tree[v_left];
		auto& tr = tree[v_right];
		auto& tv = tree[v];
		for (int li = 0, ri = 0; li < tl.size() && ri < tr.size(); ) {
			if (tl[li] <= tr[ri]) tv.push_back(tl[li++]);
			else tv.push_back(tr[ri++]);
		}
		tv.push_back(inf);
	}
	
	vector<T> array;
	void build_tree(int v, int left, int right) {
		if (left + 1 == right) {
			tree[v] = { array[left], inf };
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			build_tree(v_left, left, mid);
			build_tree(v_right, mid, right);
			update_vertex(v, v_left, v_right);
		}
	}
	
	T limit, none;
	T get_vertex(int v) {
		auto& tv = tree[v];
		auto up_it = upper_bound(tv.begin(), tv.end(), limit);
		return (up_it == tv.begin() ? none : *prev(up_it));
	}
	
	T res;
	int start, end;
	void get_tree(int v, int left, int right) {
		if (start <= left && right <= end) {
			res = max(res, get_vertex(v));
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			if (start < mid) get_tree(v_left, left, mid);
			if (mid < end) get_tree(v_right, mid, right);
		}
	}
	
public:
	
	SegmentTree(int n, T _inf)
	: size(n)
	, inf(_inf)
	, tree(size << 2) {
		
	}
	
	void build(const vector<T>& _array) {
		array = _array;
		build_tree(1, 0, size);
	}
	
	T get(int _start, int _end, T _limit, T _none) {
		start = _start;
		end = _end + 1;
		limit = _limit;
		none = _none;
		
		res = none;
		get_tree(1, 0, size);
		return res;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (int& v : a) cin >> v;
	
	SegmentTree<int> tree(n, std::numeric_limits<int>::max());	
	tree.build(a);
	
	int m;
	cin >> m;
	
	while (m --> 0) {
		int l, r, x;
		cin >> l >> r >> x;
		
		int ans = tree.get(l - 1, r - 1, x, -1);
		cout << ans << "\n";
	}
	
	return 0;
}