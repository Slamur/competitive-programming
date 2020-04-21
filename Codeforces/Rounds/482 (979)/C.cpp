#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

const char SPACE = ' ', ENDL = '\n';

int ri() {
	int v;
	cin >> v;
	return v;
}

vi rvi(int n) {
	vi a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	return a;
}

int x, y;
vector<vi> graph;

vi sizes;
int yt;

bool dfs(int f, int p = -1) {

	bool was = f == y;

	sizes[f] = 1;

	for (int t : graph[f]) {
		if (t == p) continue;

		bool wt = dfs(t, f);

		if (f == x) {
			if (wt) {
				yt = t;
			}
		}

		sizes[f] += sizes[t];

		was |= wt;
	}

	return was;
}

/**
#graph
#tree
#dfs
#subtree size
*/

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
	
	for (int t = 0; t < tests; ++t) {
		int n = ri();
		x = ri() - 1;
		y = ri() - 1;

		graph.assign(n, vi());
		for (int i = 0; i < n - 1; ++i) {
			int f = ri() - 1;
			int t = ri() - 1;
			graph[f].push_back(t);
			graph[t].push_back(f);
		}

		sizes.assign(n, 0);

		dfs(x);

		ll answer = n * (n - 1LL);
		answer -= (sizes[x] - sizes[yt]) * 1LL * (sizes[y]);

		cout << answer << endl;
	}

	return 0;
}