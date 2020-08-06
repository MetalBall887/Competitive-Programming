#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//First of all, notice that subtree query => segment query if the vertices are ordered by dfs.
//Let's perform a dfs keeping a data structure that remembers how many vertices have at least one of the colors our current vertex has. It will be a segment tree
//where we keep our vertices in dfs order and when we need to paint a subtree, we paint a corresponding segment. Generally range addition and the number of non-zero
//elements is harder but here we have a rule that elements are always non-negative, so we can do it with usual range query subtree even without lazy propagation.
 
//using namespace __gnu_pbds;
 
#define N 1000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int MAXN = 1e8;
 
int n, m, tin[N], ans[N];
int timer, s[N], cur;
 
vector <int> g[N];
vector <int> q[N];
 
struct SegTree {
	int t[N], ta[N], start;
 
	void build (int n) {
		start = 1;
		while (start < n) start <<= 1;
	}
 
	void update (int node, int tl, int tr, int l, int r, int d) {
		if (r < tl || tr < l) return;
		if (l <= tl && tr <= r) {
			ta[node] += d;
			if (ta[node]) t[node] = tr - tl + 1;
			else t[node] = t[2 * node] + t[2 * node + 1];
			return;
		}
 
		int tm = (tl + tr) / 2;
 
		update (2 * node, tl, tm, l, r, d);
		update (2 * node + 1, tm + 1, tr, l, r, d);
		
		if (ta[node]) t[node] = tr - tl + 1;
		else t[node] = t[2 * node] + t[2 * node + 1];
	}
 
	void update (int l, int r, int d) {
		update (1, 0, start - 1, l, r, d);
	}
 
	int get () { return t[1]; }
} t;
 
int topsort (int x, int p) {
	s[x] = 1;
	tin[x] = timer++;
 
	for (int to : g[x])
		if (to != p) s[x] += topsort (to, x);
 
	return s[x];
}
 
void dfs (int x, int p) {
	if (!q[x].empty ()) q[x].push_back (x);
 
	for (auto a : q[x]) {
		t.update (tin[a], tin[a] + s[a] - 1, 1);
	}
 
	for (int to : g[x])
		if (to != p) dfs (to, x);
 
	ans[x] = t.get ();
 
	for (auto a : q[x]) {
		t.update (tin[a], tin[a] + s[a] - 1, -1);
	}
}
 
int main () {
	cin >> n >> m;
 
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
 
		g[u].push_back (v);
		g[v].push_back (u);
	}
 
	topsort (0, -1);
 
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		q[a].push_back (b);
		q[b].push_back (a);
	}
 
	t.build (timer + 1);
 
	dfs (0, -1);
 
	for (int i = 0; i < n; i++) {
		cout << max (0, ans[i] - 1) << ' ';
	}
}
