#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
 
//using namespace __gnu_pbds;

//Create an auxiliary binary tree-like graph where leaves are vertices and edges are directed from higher to lower levels. Now to connect a vertex to a range
//you only need to connect it with O(logn) vertices in the auxiliary graph. The same thing we can do to connect a range to a vertex but edges in a tree are
//directed towards higher vertices.
 
#define N 2000001
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
vector < pair <int, ll> > g[N];
 
ll d[N];
int n, m, start, offset, s;
 
void build_graph (int n) {
	start = 1;
	while (start < n) start <<= 1;
	offset = 2 * start + 1;
	for (int i = 1; i < start; i++) {
		g[i].push_back ({2 * i, 0});
		g[i].push_back ({2 * i + 1, 0});
 
		g[2 * i + offset].push_back ({i + offset, 0});
		g[2 * i + 1 + offset].push_back ({i + offset, 0});
	}
 
	for (int i = start; i < 2 * start; i++)
		g[i].push_back ({i + offset, 0});
}
 
void out_conn (int x, int l, int r, ll w) {
	l += start, r += start + 1;
	x += start;
 
	while (l < r) {
		if (l & 1) g[x].push_back ({l++, w});
		if (r & 1) g[x].push_back ({--r, w});
		l >>= 1, r >>= 1;
	}
}
 
void sing_conn (int u, int v, ll w) {
	u += start, v += start;
	g[u].push_back ({v, w});
}
 
void in_conn (int x, int l, int r, ll w) {
	l += start, r += start + 1;
	x += start;
 
	while (l < r) {
		if (l & 1) g[offset + l++].push_back ({x, w});
		if (r & 1) g[--r + offset].push_back ({x, w});
		l >>= 1, r >>= 1;
	}
}
 
int main () {
	cin >> n >> m >> s;
 
	build_graph (n);
 
	s--;
	s += start;
 
	for (int i = 0; i < m; i++) {
		int t;
		cin >> t;
 
		if (t == 1) {
			int u, v, w;
			cin >> u >> v >> w;
			u--, v--;
			sing_conn (u, v, w);
		} else {
			int u, l, r, w;
			cin >> u >> l >> r >> w;
			u--, l--, r--;
			if (t == 2) out_conn (u, l, r, w);
			else in_conn (u, l, r, w);
		}
	}
 
	fill (d, d + 4 * start + 2, INF);
	d[s] = 0;
 
	priority_queue < pair <ll, int> > q;
 
	q.push ({0, s});
 
	while (!q.empty ()) {
		auto x = q.top ();
		q.pop ();
 
		if (-x.first != d[x.second]) continue;
 
		for (auto to : g[x.second]) {
			if (d[to.first] > d[x.second] + to.second) {
				d[to.first] = d[x.second] + to.second;
				q.push ({-d[to.first], to.first});
			}
		}
	}
 
	for (int i = 0; i < n; i++) {
		cout << (d[start + i] == INF ? -1 : d[start + i]) << ' ';
	}
 
 
}
