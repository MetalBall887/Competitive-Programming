#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//The greedy solution will work. Let's say we have a partial assignment, with numbers 1..t, given first i edges are already assigned. By induction, we suppose 
//that all assigned edges are assigned in the optimal way, i.e. when setting i-th edge you can't touch any assigned numbers/edges or else the answer will lose 
//the minimality. Now let's try to assign the i-th edge. Obviously, minimizing it is first priority after not changing the existing assignment. If it belongs 
//to R, just give it number t+1. If it does not, look at edges in R that form a path between endpoints of the i-th edge. All these edges should have lower weights
//than the i-th one, so that i-th one is not included to the spanning tree by the red rule. Still, we want to minimize the current edge, so take all unassigned
//edges from the path and assign t+1, t+2,...,t'-1 for them. Then assign t' to the current edge. If we also sort the weights on the newly assigned edges on the 
//path by the order number, we can see that after any change either t' will increase or the ordering in t+1...t'-1 will stop being sorted.
 
using namespace __gnu_pbds;
 
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;

const int N = 2000001;
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

vector < pair <int, int> > g[N];

struct DSU {
	int p[N];

	void fill (int n) {
		for (int i = 0; i < n; i++) {
			p[i] = i;
		}
	}

	int find (int x) {
		if (x == p[x]) return x;
		return p[x] = find (p[x]);
	}

	void unite (int a, int b) {
		a = find (a), b = find (b);

		if (a == b) return;

		p[b] = a;
	}
} dsu;

int n, t, r[N], p[N][20], tin[N], tout[N], m;
pair <int, int> e[N];
pair <int, int> p_edge[N];
int ans[N], timer;

void dfs (int x, int pr, int nm) {
	tin[x] = ++timer;
	p[x][0] = pr;
	p_edge[x] = {pr, nm};

	for (int i = 1; i < 20; i++) {
		p[x][i] = p[p[x][i-1]][i-1];
	}

	for (auto [to, nm] : g[x]) {
		if (to != pr) dfs (to, x, nm);
	}
	tout[x] = ++timer;
}

bool parent (int a, int b) {
	return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int lca (int a, int b) {
	if (parent (a, b)) return a;
	if (parent (b, a)) return b;

	for (int i = 19; i >= 0; i--) {
		if (!parent (p[a][i], b)) a = p[a][i];
	}

	return p[a][0];
}

int main () {
	cin >> n >> m;

	dsu.fill (n);

	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		a--, b--;

		e[i] = {a, b};
	}

	for (int i = 0; i < n - 1; i++) {
		int x;
		cin >> x;
		x--;
		r[x] = 1;
		auto [a, b] = e[x];
		g[a].push_back ({b, x});
		g[b].push_back ({a, x});
	}

	dfs (0, 0, -1);

	for (int i = 0; i < m; i++) {
		vector <int> v;

		auto [a, b] = e[i];
		
		if (r[i]) {
			if (!ans[i]) {
				ans[i] = ++t;
				if (parent (b, a)) swap (a, b);
				dsu.unite(a, b);
			}
			continue;
		}

		int l = lca (a, b);

		int x = dsu.find (a);

		while (!parent (x, l)) {
			v.push_back(p_edge[x].second);
			dsu.unite (p_edge[x].first, x);
			x = dsu.find (x);
		}

		x = dsu.find (b);

		while (!parent (x, l)) {
			v.push_back(p_edge[x].second);
			dsu.unite (p_edge[x].first, x);
			x = dsu.find (x);
		}

		sort (v.begin(), v.end());

		for (auto a : v) {
			ans[a] = ++t;
		}

		ans[i] = ++t;
	}

	for (int i = 0; i < m; i++) {
		cout << ans[i] << ' ';
	}
}
