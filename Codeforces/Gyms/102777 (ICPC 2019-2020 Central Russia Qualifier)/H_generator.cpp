#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int max_n = 1e9 + 1;
	ll mod = 1e9 + 7;
	
	int block = 1e6;
	
	ll fp2 = 1, fpp3 = 1;
	for (int i = 3, it = 3; i < max_n; ++i, ++it) {
		ll f = 2 * fp2 + 3 * fpp3 + i;
		f %= mod;
		
		if (it == 3) {
			cout << ", " << fpp3 << ", " << fp2;
			}
			
		if (it == block) {
			it = 0;
		}
		
		
		fpp3 = fp2;
		fp2 = f;
	}
	
	return 0;
}
