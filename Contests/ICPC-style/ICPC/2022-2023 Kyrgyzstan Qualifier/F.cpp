#include <bits/stdc++.h>

using namespace std;

using ll = int64_t;

int main() {
	ll left, right;
	cin >> left >> right;
	
	ll max_possible_yes = 5;
	
	auto get_answer = [&]() {
		ll size = (right - left + 1);
		if (size > max_possible_yes) {
			return false;
		}
		
		/*
		vector<ll> squares;
		for (ll a = 0; a * a <= right; ++a) squares.push_back(a * a);
		
		auto check = [&](ll x) {
			for (int ai = 0, bi = squares.size() - 1; squares[ai] * 2 <= x; ++ai) {
				ll a2 = squares[ai];
				while (bi > ai && squares[bi] > x - a2) --bi;
				if (a2 + squares[bi] == x) return true;
			}
			
			return false;
		};
		*/
		
		auto check = [&](ll x) {
		    for (ll a = 0; 2 * a * a <= x; ++a) {
		        ll b2 = x - a * a;
		        
		        ll b = sqrt(b2);
		        while (b * b > b2) --b;
		        while ((b + 1) * (b + 1) <= b2) ++b;
		        
		        if (b * b == b2) return true;
		    }  
		    
		    return false;
		};
		
		bool can = true;
		for (ll x = left; x <= right; ++x) can &= check(x);
		
		return can;
	};
	
	cout << (get_answer() ? "Yes" : "No") << "\n";

	return 0;
}
