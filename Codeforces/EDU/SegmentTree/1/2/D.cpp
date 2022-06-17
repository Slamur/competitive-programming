#include <bits/stdc++.h>

using namespace std;

void init_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	cout << setprecision(10) << fixed;
}

using ll = int64_t;

class SegmentTree {
public:
	using T = ll;
private:
	int size;
	T neutral;
	vector<T> tree;
		
	void set_vertex(int v, int _value) {
		tree[v] = _value;
	}
	
	void clear(int v) {
		set_vertex(v, neutral);
	}
	
	void merge(int target, int source) {
		tree[target] = max(tree[target], tree[source]);
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
	
	int no_ans = -1;
	
	int need;
	void find_tree_seg(int v, int left, int right) {
		if (start <= left && right <= end) {
			if (tree[v_res] != no_ans) return;
			
			int ans = find_tree(v, left, right);
			if (ans != no_ans) {
				set_vertex(v_res, ans);
			}
		} else {
			int mid = (left + right) / 2;
			int v_left = (v << 1), v_right = v_left + 1;
			if (start < mid) find_tree_seg(v_left, left, mid);
			if (mid < end) find_tree_seg(v_right, mid, right);
		}
	}
	
	T find_tree(int v, int left, int right) {
		if (tree[v] < need) return no_ans;
		
		if (left + 1 == right) {
			return left;
		} else {
			int mid = (left + right) / 2;
			int v_left = (v << 1), v_right = v_left + 1;
			
			if (tree[v_left] >= need) {
				return find_tree(v_left, left, mid);
			} else {
				return find_tree(v_right, mid, right);
			}
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
	
	int find_seg(int _need, int _start, int _end) {
		need = _need;
		
		start = _start;
		end = _end + 1;
		
		set_vertex(v_res, no_ans);
		find_tree_seg(1, 0, size);
		
		return tree[v_res];
	}
};

SegmentTree create_tree(vector<int>& a) {
	 int inf = numeric_limits<int>::min();
	SegmentTree::T neutral = ll(inf);
	
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
	
	while (q --> 0) {
		int type;
		cin >> type;
		
		if (SET == type) {
			int index, value;
			cin >> index >> value;
			
			tree.set(index, value);
		} else {
			int x, start, end;
			cin >> x >> start;
			
			end = n - 1;
			
			cout << tree.find_seg(x, start, end) << "\n";
		}
	}
	
	return 0;
}
