#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

class BinaryJumps {
private:
	vector<vector<int>> jumps;
	int log_2;
	
public:
	BinaryJumps(vector<int>& base_jumps, ll max_steps) {
		log_2 = 0;
		while ((1LL << log_2) <= max_steps) ++log_2;
		
		int n = base_jumps.size();
		jumps.assign(log_2, vector<int>(n + 1, 0));
		
		for (int v = 0; v < n; ++v) {
			jumps[0][v + 1] = base_jumps[v];
		}
		
		for (int b = 0; b + 1 < log_2; ++b) {
			for (int v = 0; v < jumps[b].size(); ++v) {
				int p = jumps[b][v];
				jumps[b + 1][v] = jumps[b][p];
			}
		}
	}
	
	int jump(int v, ll steps) {
		for (int b = log_2; b >= 0; --b) {
			ll cur_step = (1LL << b);
			if (steps >= cur_step) {
				steps -= cur_step;
				v = jumps[b][v];
			}
		}
		
		return v;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;
	
	vector<int> lefts(n);
	for (int& v : lefts) cin >> v;
	
	vector<int> rights(n);
	for (int& v : rights) cin >> v;
	
	ll max_steps = 1e15;
	BinaryJumps lj(lefts, max_steps);
	BinaryJumps rj(rights, max_steps);
	
	while (q --> 0){
		int x;
		ll a, b;
		int c;
		
		cin >> x >> a >> b >> c;
		
		if (c == 0) {
			x = lj.jump(x, a);
			x = rj.jump(x, b);
		} else {
			x = rj.jump(x, b);
			x = lj.jump(x, a);
		}
		
		cout << x << "\n";
	} 	
	
	return 0;
}
