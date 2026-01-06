#include <bits/stdc++.h>

using namespace std;

void init_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	cout << setprecision(10) << fixed;
}

using ll = int64_t;

struct Node {
	ll total;
	ll pref, suff;
	ll opt;
	
	Node(int value) {
		set(value);
	}
	
	void set(int value) {
		total = value;
		pref = max(value, 0);
		suff = max(value, 0);
		opt = max(value, 0);
	}
	
	void merge(const Node& source) {
		ll candidate = suff + source.pref;
		ll comb_pref = total + source.pref;
		ll comb_suff = source.total + suff;
		
		total += source.total;
		opt = max(opt, max(candidate, source.opt));
		
		pref = max(pref, comb_pref);
		suff = max(source.suff, comb_suff);
	}
};

class SegmentTree {
public:
	using T = Node;
private:
	int size;
	T neutral;
	vector<T> tree;
		
	void set_vertex(int v, int _value) {
		tree[v].set(_value);
	}
	
	void clear(int v) {
		set_vertex(v, neutral.total);
	}
	
	void merge(int target, int source) {
		tree[target].merge(tree[source]);
	}
	
	void update_vertex(int v, int v_left, int v_right) {
		clear(v);
		merge(v, v_left);
		merge(v, v_right);
	}
	
	vector<int> a;
	void build_tree(int v, int left, int right) {
		if (left + 1 == right) {
			set_vertex(v, a[left]);
		} else {
			int mid = (left + right) / 2;
			int v_left = (v << 1), v_right = v_left + 1;
			build_tree(v_left, left, mid);
			build_tree(v_right, mid, right);
			update_vertex(v, v_left, v_right);
		}
	}
	
	int index;
	int value;
	
	void set_tree_pos(int v, int left, int right) {
		if (left + 1 == right) {
			set_vertex(v, value);
		} else {
			int mid = (left + right) / 2;
			int v_left = (v << 1), v_right = v_left + 1;
			if (index < mid) set_tree_pos(v_left, left, mid);
			else set_tree_pos(v_right, mid, right);
			update_vertex(v, v_left, v_right);
		}
	}
	
	int v_res = 0;
	int start, end;
	
	void get_tree_seg(int v, int left, int right) {
		if (start <= left && right <= end) {
			merge(v_res, v);
		} else {
			int mid = (left + right) / 2;
			int v_left = (v << 1), v_right = v_left + 1;
			if (start < mid) get_tree_seg(v_left, left, mid);
			if (mid < end) get_tree_seg(v_right, mid, right);
		}
	}

public:
	SegmentTree(int n, T _neutral)
	: size(n)
	, neutral(_neutral)
	, tree(size << 2, neutral)
	{ }
	
	void build(vector<int>& _a) {
		a = _a;
		build_tree(1, 0, size);
	}
	
	void set(int _index, int _value) {
		index = _index;
		value = _value;
		set_tree_pos(1, 0, size);
	}
	
	const T& get_max_sum(int _start, int _end) { // [_start, _end]
		start = _start;
		end = _end + 1;
		
		clear(v_res);
		get_tree_seg(1, 0, size);
		return tree[v_res];
	}
};

SegmentTree create_tree(vector<int>& a) {
	int inf = numeric_limits<int>::max();
	SegmentTree::T neutral = Node(0);
	
	SegmentTree tree(a.size(), neutral);
	
	tree.build(a);
	return tree;
}

int main() {
	init_io();
	
	int n, q;
	cin >> n >> q;
	
	vector<int> a(n);
	for (int& v : a) cin >> v;
	
	SegmentTree tree = create_tree(a);
	
	const int SET = 1;
	
	cout << tree.get_max_sum(0, n - 1).opt << "\n";
	
	while (q --> 0) {
		int type;
		//cin >> type;
		type = SET;
		
		if (SET == type) {
			int index, value;
			cin >> index >> value;
			
			tree.set(index, value);
			cout << tree.get_max_sum(0, n - 1).opt << "\n";
		}
	}
	
	return 0;
}
