#include <bits/stdc++.h>

using namespace std;

void init_io() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
 
	cout << setprecision(10) << fixed;
}

using ll = int64_t;

int mod;

class Matrix {
public:
	int a, b, c, d; 
	// a b
	// c d
	
	Matrix() {
	}
	
	Matrix(int _a, int _b, int _c, int _d)
	: a(_a)
	, b(_b)
	, c(_c)
	, d(_d)
	{ }
	
	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			a = other.a;
			b = other.b;
			c = other.c;
			d = other.d;
		}
		
		return *this;
	}
	
	Matrix& operator*=(const Matrix& o) {
		/*
		 * res_a = a * oa + b * oc
		 * res_b = a * ob + b * od
		 * res_c = c * oa + d * oc
		 * res_d = c * ob + d * od
		 */
		 
		 int res_a = (a * o.a + b * o.c) % mod;
		 int res_b = (a * o.b + b * o.d) % mod;
		 int res_c = (c * o.a + d * o.c) % mod;
		 int res_d = (c * o.b + d * o.d) % mod;
		 
		 a = res_a;
		 b = res_b;
		 c = res_c;
		 d = res_d;
		 
		 return *this;
	}
};

ostream& operator<<(ostream& out, const Matrix& matrix) {
	out << matrix.a << " " << matrix.b << "\n" << matrix.c << " " << matrix.d << "\n";
	return out;
}

istream& operator>>(istream& in, Matrix& matrix) {
	int a, b, c, d;
	in >> a >> b >> c >> d;
	
	matrix.a = a;
	matrix.b = b;
	matrix.c = c;
	matrix.d = d;
	
	return in;
}

class SegmentTree {
public:
	using T = Matrix;
private:
	int size;
	T neutral;
	vector<T> tree;
	
	void clear(int v) {
		tree[v] = neutral;	
	}
	
	void merge(int target, int source) {
		tree[target] *= tree[source];
	}
	
	void update_vertex(int v, int v_left, int v_right) {
		clear(v);
		merge(v, v_left);
		merge(v, v_right);
	}
	
	vector<T> a;
	void build_tree(int v, int left, int right) {
		if (left + 1 == right) {
			tree[v] = a[left];
		} else {
			int mid = (left + right) / 2;
			int v_left = (v << 1), v_right = (v_left + 1);
			build_tree(v_left, left, mid);
			build_tree(v_right, mid, right);
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
			int v_left = (v << 1), v_right = (v_left + 1);
			if (start < mid) get_tree_seg(v_left, left, mid);
			if (mid < end) get_tree_seg(v_right, mid, right);
		}
	}
	
public:
	SegmentTree(int _size, const T& _neutral)
	: size(_size)
	, neutral(_neutral)
	, tree(size << 2, neutral)
	{ }
	
	void build(const vector<T>& _a) {
		a = _a;
		build_tree(1, 0, size);
	}
	
	const T& get_product(int _start, int _end) {
		start = _start;
		end = _end + 1;
		
		clear(v_res);
		get_tree_seg(1, 0, size);
		return tree[v_res];
	}
};

SegmentTree create_tree(const vector<Matrix>& a) {
	Matrix neutral(1, 0, 0, 1);
	SegmentTree tree(a.size(), neutral);
	tree.build(a);
	return tree;
}

int main() {
	init_io();
	
	int n, q;
	cin >> mod >> n >> q;
	
	vector<Matrix> a(n);
	for (auto& matrix : a) cin >> matrix;
	
	SegmentTree tree = create_tree(a);
	
	for (int it = 0; it < q; ++it) {
		int start, end;
		cin >> start >> end;
		--start, --end;
		
		auto& res = tree.get_product(start, end);
		cout << res << "\n";
	}
	
	return 0;
}
