#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int gcd(int a, int b) {
	return (a == 0 ? b : gcd(b % a, a));
}

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
		tree[v_to] = gcd(tree[v_from], tree[v_to]);
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
			if (tree[v] % need != 0) {
				search_tree_pos(v, left, right);
				found = true;
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
			if (tree[v_left] % need != 0) {
				search_tree_pos(v_left, left, mid);
			} else {
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
	
	int search(int _start, int _end, T _need) {
		need = _need;
		found = false;
		
		start = _start;
		end = _end + 1;
		
		search_tree_seg(1, 0, size);
		
		return index;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n;
	cin >> n;
	
	vector<int> a(n + 1, 0);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	SegmentTree<int> tree(n + 1, 0);
	tree.build(a);
	
	int q;
	cin >> q;
	
	const int ASK_SEG = 1, SET_POS = 2;
	while (q --> 0) {
		int type;
		cin >> type;
		
		if (ASK_SEG == type) {
			int start, end, x;
			cin >> start >> end >> x;

			bool can = true;
			
			int total = tree.get(start, end);
			if (total % x != 0) {
				int first = tree.search(start, end, x);
				int suffix = (first < end ? tree.get(first + 1, end) : 0);				
				can = (suffix % x == 0);
			}
			
			cout << (can ? "YES" : "NO") << "\n";
		} else {
			int index, value;
			cin >> index >> value;
			
			tree.update(index, value);
		}
	}
	
	return 0;
}