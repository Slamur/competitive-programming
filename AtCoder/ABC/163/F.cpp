#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <string>
#include <map>
#include <set>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const int MODULO = 1e9 + 7;

typedef ll mod_t;

const char SPACE = ' ', ENDL = '\n';

int ri() {
	int v;
	cin >> v;
	return v;
}

ll rll() {
	ll v;
	cin >> v;
	return v;
}

vi rvi(int n) {
	vi a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	return a;
}

vector<ll> cnt;

vi c;
vector<vi> g;
vector<ll> sz;
vector<ll> cs;

int dfs_down(int f, int p = -1) {
	ll s = 1;

	ll & ans = cnt[c[f]];
	ans++; // [f -> f]

	for (int t : g[f]) {
		if (t != p) {
			ll ts = dfs_down(t, f);

			ans += ts * s;
			s += ts;
		}
	}

	return sz[f] = s;
}

void dfs_up(int f, int p = -1) {
	int col = c[f];

	ll old_cs = cs[col];

	for (int t : g[f]) {
		if (t == p) continue;

		cs[col] = sz[t];
		dfs_up(t, f);
	}

	cs[col] = old_cs - sz[f];

	cnt[col] += sz[f] * cs[col];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int tests =
#ifdef ONLINE_JUDGE
		1;
#else
		ri();
#endif

	/*
	graph
	tree
	dfs
	*/

	for (int t = 0; t < tests; ++t) {
		int n = ri();
		c = rvi(n);

		g.assign(n, vi(0));
		for (int i = 0; i < n - 1; ++i) {
			int f = ri() - 1;
			int t = ri() - 1;

			g[f].push_back(t);
			g[t].push_back(f);
		}

		cnt.assign(n + 1, 0);

		sz.assign(n, 0);
	
		int root = 0;
		dfs_down(root);

		cs.assign(n + 1, n);
		dfs_up(root);

		for (int c = 1; c <= n; ++c) {
			cout << cnt[c] << ENDL;
		}
	}

	return 0;
}