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
			clear(v);
			accumulate(v, v_res);
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			if (index < mid) update_tree(v_left, left, mid);
			else update_tree(v_right, mid, right);
			update_vertex(v, v_left, v_right);
		}
	}
	
	T need;
	bool found;
	void search_tree_seg(int v, int left, int right) {
		if (found) return;
		
		if (start <= left && right <= end) {
			if (need <= tree[v]) {
				search_tree_pos(v, left, right);
				found = true;
			} else {
				need -= tree[v];
			}
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			if (start < mid) search_tree_seg(v_left, left, mid);
			if (mid < end) search_tree_seg(v_right, mid, right);
		}
	}
	
	void search_tree_pos(int v, int left, int right) {
		if (left + 1 == right) {
			index = left;
		} else {
			int mid = (left + right) / 2;
			int v_left = v * 2, v_right = v_left + 1;
			if (need <= tree[v_left]) {
				search_tree_pos(v_left, left, mid);
			} else {
				need -= tree[v_left];
				search_tree_pos(v_right, mid, right);
			}
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
	
	int search(int _start, T _need) {
		need = _need;
		found = false;
		
		start = _start;
		end = size;
		
		search_tree_seg(1, 0, size);
		
		return index;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, k;
	cin >> n >> k;
	
	SegmentTree<ll> tree(n + 1, 0);
	
	vector<ll> array(n + 1, 1);
	array[0] = 0;
	
	tree.build(array);
	
	vector<int> order;
	
	int last = 0;
	for (int alive = n; alive >= 1; --alive) {
		int need = k % alive;
		if (0 == need) need = alive;
		
		int suffix = tree.get(last, n);
		
		int next = -1;
		if (suffix >= need) {
			next = tree.search(last, need);
		} else {
			need -= suffix;
			next = tree.search(0, need);
		}
		
		order.push_back(next);
		
		tree.update(next, 0);
		last = next;
	}
	
	for (int v : order) cout << v << " ";
	cout << "\n";
	
	return 0;
}