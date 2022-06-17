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
	T value;
	
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
	
	SegmentTree(int n, T _neutral)
	: size(n)
	, neutral(_neutral)
	, tree(size << 2, neutral) {
		
	}
	
	T get_pos(int _index) {
		start = 0;
		end = _index;
		
		clear(v_res);
		get_tree(1, 0, size);
		return tree[v_res];
	}
	
	void update_pos(int _index, T delta) {
		index = _index;
		
		set(v_res, delta);
		update_tree(1, 0, size);
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	
	SegmentTree<ll> tree(n + 1, 0);
	
	const int UPDATE_SEGMENT = 1, GET_POS = 2;
	for (int i = 0; i < m; ++i) {
		int type;
		cin >> type;
		
		if (UPDATE_SEGMENT == type) {
			int start, end;
			ll delta;
			cin >> start >> end >> delta;
			
			tree.update_pos(start - 1, delta);
			tree.update_pos(end, -delta);
		} else {
			int index;
			cin >> index;
			
			cout << tree.get_pos(index) << "\n";
		}
	}
	
	return 0;
}