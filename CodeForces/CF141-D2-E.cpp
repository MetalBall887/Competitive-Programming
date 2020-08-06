#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//Let's call edges that santa can clear black, other white. We need to find a spanning tree of a graph, so that the number of black edges will equal the number of
//white ones in it. Let's consider white spanning forest as a spanning forest for a subgraph for only and all white edges and the same way for a black spanning 
//forest. Also let's look at a union of these two forests. It has two properties: 1) It has O(n) edges 2) There are no all-black and all-white cycles. Last means,
//each cycle will have at least one white and at least one black edge. This is good, because we can construct a spanning tree from this union graph by "cutting"
//cycles and in each cycle we can choose an edge of which color to cut. Now it can be shown that if n-1 is even and 
//min(|black spanning forest|, |white spanning forest|) <= (n-1) / 2, then there is a way to cut enough edges of each color to get the needed balance.
//The algorithm is simple: find any cycle, there will be edges of both colors in it. Choose the color you need to get rid off and erase the edge. Also check if
//the union graph is connected.

using namespace __gnu_pbds;
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;
 
struct edge {
	int u, v, t, id;
} tb, tw, p[1000];
 
int n, m, u[1000], ban[N];
 
vector <edge> g[N];
 
inline void take (edge a) {
	if (a.t) tw = a;
	else tb = a;
}
 
bool cycle_dfs (int x, int pid) {
	u[x] = 1;
 
	for (auto e : g[x]) {
		int to = e.v;
 
		if (pid == e.id || ban[e.id] || u[to] == 2) continue;
 
		if (u[to] == 1) {
			int a = x;
			take (e);
			while (a != to) {
				take (p[a]);
				a = p[a].u;
			}
 
			return true;
		}
 
		p[to] = e;
		if (cycle_dfs (to, e.id)) return true;
	}
 
	u[x] = 2;
 
	return false;
}
 
struct DSU {
	int p[1000], sz[1000], comp;
 
	DSU () {
		for (int i = 0; i < 1000; i++) {
			p[i] = i, sz[i] = 1;
		}
 
		comp = n;
	}
 
	int find (int x) {
		if (x == p[x]) return x;
		return p[x] = find (p[x]);
	}
 
	bool unite (int a, int b) {
		a = find (a), b = find (b);
 
		if (a == b) return false;
		if (sz[a] < sz[b]) swap (a, b);
 
		sz[a] += sz[b];
		p[b] = a;
		comp--;
 
		return true;
	}
} dw, db, dsu;
 
vector <edge> e;
 
int main () {
	cin >> n >> m;
 
	for (int i = 0; i < m; i++) {
		int u, v;
		string c;
		cin >> u >> v >> c;
		e.push_back ({u - 1, v - 1, (c == "S"), i});
	}
 
	int w_size = 0, b_size = 0;
 
	dsu.comp = n;
 
	for (auto x : e) {
		dsu.unite (x.u, x.v);
		if (x.t) {
			if (dw.unite (x.u, x.v)) {
				g[x.u].push_back ({x.u, x.v, x.t, x.id});
				g[x.v].push_back ({x.v, x.u, x.t, x.id});
				w_size++;
			} else { ban[x.id] = 1; }
		} else {
			if (db.unite (x.u, x.v)) {
				g[x.u].push_back ({x.u, x.v, x.t, x.id});
				g[x.v].push_back ({x.v, x.u, x.t, x.id});
				b_size++;
			} else { ban[x.id] = 1; }
		}
	}
 
	while (w_size + b_size >= n) {
		for (int i = 0; i < n; i++) {
			if (cycle_dfs (i, -1)) {
				if (w_size > b_size) {
					w_size--;
					ban[tw.id] = 1;
				} else {
					b_size--;
					ban[tb.id] = 1;					
				}
 
				break;
			}
		}
 
		fill (u, u + n, 0);
		fill (p, p + n, edge ({0, 0, 0, 0}));
	}
 
	if (w_size != b_size || dsu.comp > 1) cout << -1;
	else {
		cout << n - 1 << endl;
 
		for (auto a : e) {
			if (!ban[a.id]) cout << a.id + 1 << ' ';
		}
	}
 
}
