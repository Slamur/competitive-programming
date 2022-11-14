#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;
using vi = vector<int>;
using vll = vector<ll>;
using ii = pair<int, int>;

void init_io(const string& filename) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	if (filename.size() > 0) {
	    freopen((filename + ".in").c_str(), "rt", stdin);
	    freopen((filename + ".out").c_str(), "wt", stdout);   
	}
	
	cout << setprecision(10) << fixed;
}

struct ConvexHull {
	int left, right;
	set<int> removed;
	
	ConvexHull(int size)
	: left(0), right(size * 2)
	{ }
	
	void remove(int coord) {
		removed.insert(coord);
		while (removed.count(left + 1)) left += 2;
		while (removed.count(right - 1)) right -= 2;
	}
	
	bool outside(ll sum, ll count) {
		return sum <= left * count || right * count <= sum;
	}
};

void solve() {
	// read
	int layer_size, width;
	cin >> layer_size >> width;
	
	int n, q;
	cin >> n >> q;
	
	vector<ii> queries(q);
	for (auto& [layer, index] : queries) {
		cin >> layer >> index;
	}
	
	// init values
	vector<ConvexHull> x_hulls(n + 1, ConvexHull(layer_size)), 
			y_hulls(n + 1, ConvexHull(layer_size));
			
	vi layer_counts(n + 1, layer_size);
			
	// 1 + 3 + 5 + ... + (2 * ls - 1) = ls^2
	// (2 * ls / 2) * ls = ls^2
	ll layer_center_sum = layer_size * layer_size;
	
	vll x_sums(n + 1, layer_center_sum), 
		y_sums(n + 1, layer_center_sum);
	
	// process queries
	auto get_answer = [&]() {	
		for (int j = 0; j < q; ++j) {
			auto& [layer, index] = queries[j];
			
			// recalc values
			layer_counts[layer]--;
			
			int coord = 2 * index - 1;
			
			auto& hulls = (layer % 2 == 0 ? x_hulls : y_hulls);
			hulls[layer].remove(coord);
			
			auto& diff_sums = (layer % 2 == 0 ? x_sums : y_sums);
			diff_sums[layer] -= coord;
			
			auto& eq_sums = (layer % 2 == 0 ? y_sums : x_sums);
			eq_sums[layer] -= layer_size;
			
			ll xs = 0, ys = 0, cnt = 0;
			for (int i = n; i > 0; --i) {
				if (i < n) {
					if (x_hulls[i].outside(xs, cnt)) return j;
					if (y_hulls[i].outside(ys, cnt)) return j;
				}
				
				xs += x_sums[i];
				ys += y_sums[i];
				cnt += layer_counts[i];
			}
		}
		
		return -1;
	};
	
	int ans = get_answer();
	if (-1 == ans) {
		cout << "no" << endl;
	} else {
		cout << "yes" << endl;
		cout << ans + 1 << endl;
	}
}

int main() {
	init_io("jenga");
	solve();
	
	return 0;
}
