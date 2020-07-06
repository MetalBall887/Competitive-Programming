#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//There is a similar problem to this one where you have to find a permutation which satisfies the same requirements. It's solved by finding the maximal matching
//in a bipartite graph where the left part is position and the right part is value and there is an edge (a, b) if there can be value b in position a. It can be
//solved by flows. Here we need to modify the network to allow several positions having the same value, so we connect each value with a sink with several edges
//of capacity 1. Costs of these edgesshould be 1, 3, 5, 7, ..., so that if we have k positions having value b, k edges will be used with the overall cost k^2.
//Now find the minimal cost flow of size if there is any.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
struct Edge {
	int u, v, to, f, cost;
	Edge *twin;
};
 
vector <Edge> g[N];
 
int p[N], S, T, n, q;
 
int cost_p (Edge e) {
	return e.cost - p[e.v] + p[e.u];
}
 
pair <int, int> find_path () {
	priority_queue < pair <int, int> > q;
	vector <int> d (T + 1, 1e9);
	vector <Edge*> par (T + 1);
	d[S] = 0;
 
	q.push ({0, S});
 
	while (!q.empty ()) {
		pair <int, int> x = q.top ();
		q.pop ();
		if (-x.first != d[x.second]) continue;
		for (Edge& to : g[x.second]) {
			if (to.f && d[to.v] > d[to.u] + cost_p (to)) {
				d[to.v] = d[to.u] + cost_p (to);
				par[to.v] = &to;
				q.push ({-d[to.v], to.v});
			}
		} 
	}
 
	for (int i = 0; i <= T; i++)
		if (d[i] < 1e9) p[i] += d[i];
 
	if (d[T] == 1e9) return {-1, 0};
 
	int x = T, cap = 1e9, cost = 0;
 
	while (x != S) {
		cap = min (cap, par[x] -> f);
		x = par[x] -> u;
	}
 
	x = T;
 
	while (x != S) {
		par[x] -> f -= cap;
		cost += cap * (par[x] -> cost);
		par[x] -> twin -> f += cap;
		x = par[x] -> u;
	}
 
	return {cap, cost};
}
 
int flow () {
	int s = 0, f = 0;
	pair <int, int> a;
	while (true) {
		a = find_path ();
		if (a.first < 0) return f == n ? s : -1;
		s += a.second;
		f += a.first;
	}
}
 
void add_edge (int u, int v, int c) {
	Edge a {u, v, (int) g[v].size (), 1, c};
	Edge b {v, u, (int) g[u].size (), 0, -c};
 
	g[u].push_back (a);
	g[v].push_back (b);
}
 
int main () {
	cin >> n >> q;
 
	vector < pair <int, int> > rn (n + 1, {1, n});
 
	for (int i = 0; i < q; i++) {
		int t, l, r, v;
		cin >> t >> l >> r >> v;
 
		if (t == 1) {
			for (int j = l; j <= r; j++)
				rn[j].first = max (rn[j].first, v);
		} else {
			for (int j = l; j <= r; j++)
				rn[j].second = min (rn[j].second, v);
		}
	}
 
	for (int i = 1; i <= n; i++) {
		add_edge (0, i, 0);
 
		for (int j = rn[i].first; j <= rn[i].second; j++) {
			add_edge (i, n + j, 0);
		}
	}
	T = 2 * n + 2;
 
	for (int i = n + 1; i <= 2 * n; i++)
		for (int j = 0; j < n; j++)
			add_edge (i, T, 2 * j + 1);
 
	for (int i = 0; i <= T; i++)
		for (Edge& x : g[i]) {
			x.twin = &g[x.v][x.to];
		}
 
	cout << flow ();
}
