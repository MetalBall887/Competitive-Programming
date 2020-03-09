#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//It is stated that for a biconnected component there is a way to erient it into SCC. Moreover, in each such connection we 
//can revert all of the edges and still get an SCC. That means, for an edge inside of biconnected component the answer is B.
//Now we can condensate the BC-components into vertices and solve the same problem for a tree by decomposing the path (x, y)
//to (x, lca) and (lca, y). 

using namespace __gnu_pbds;

#define N 2000001

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;

int u[N], timer, tin[N], fup[N], lg[N], n, m, p, x, y;
int col[N], l[N], r[N], h[N];
vector <int> g[N], gt[N], v;
vector <pair <int, int>> e;
set <pair <int, int>> s, br;

void dfs (int x, int p) {
	bool back = true;
	u[x] = true;
	fup[x] = tin[x] = ++timer;
	for (int to : g[x]) {
		if (to == p && back) {
			back = false;
			continue;
		}

		if (u[to]) {
			fup[x] = min (fup[x], tin[to]);
		} else {
			dfs (to, x);
			fup[x] = min (fup[x], fup[to]);
			if (fup[to] > tin[x]) {
				br.insert ({x, to});
				br.insert ({to, x});
			}
		}
	}
}

void color (int x, int c) {
	col[x] = c;

	for (int to : g[x]) {
		if (col[to] || br.count ({x, to})) continue;
		color (to, c);
	}
}

void dfs_tree (int x, int p) {
	u[x] = 1;
	if (p != -1) h[x] = h[p] + 1;
	else h[x] = 1;

	for (int to : gt[x]) {
		if (to == p) continue;
		dfs_tree (to, x);
	}
}

int final_dfs (int x, int p) {
	int cur = l[x];
	u[x] = 1;

	for (int to : gt[x]) {
		if (to == p) continue;
		cur += final_dfs (to, x);
	}

	if (cur > 0) s.insert ({x, p});
	else if (cur < 0) s.insert ({p, x});

	return cur;
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		e.push_back ({u, v});
		g[u].push_back (v);
		g[v].push_back (u);
	}

	for (int i = 0; i < n; i++)
		if (!u[i]) dfs (i, -1);

	int cl = 0;
	timer = 0;

	for (int i = 0; i < n; i++)
		if (!col[i]) color (i, ++cl);

	n = cl;

	for (int i = 0; i < m; i++) {
		if (col[e[i].first] != col[e[i].second]) {
			gt[col[e[i].first] - 1].push_back (col[e[i].second] - 1);
			gt[col[e[i].second] - 1].push_back (col[e[i].first] - 1);
		}
	}

	memset (u, 0, sizeof (u));

	for (int i = 0; i < n; i++)
		if (!u[i]) dfs_tree (i, -1);

	cin >> p;

	for (int i = 0; i < p; i++) {
		cin >> x >> y;
		x = col[x-1] - 1, y = col[y-1] - 1;

		l[x]++, l[y]--;
	}

	memset (u, 0, sizeof (u));

	for (int i = 0; i < n; i++) {
		if (!u[i]) final_dfs (i, -1);
	}

	for (int i = 0; i < m; i++) {
		int x = col[e[i].first] - 1, y = col[e[i].second] - 1;

		if (s.count ({x, y})) cout << "R";
		else if (s.count ({y, x})) cout << "L";
		else cout << "B";
	}
}
