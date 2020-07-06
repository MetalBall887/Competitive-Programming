#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//https://codeforces.com/blog/entry/63544
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e18 + 7, MOD2 = 1e6 + 3;
 
struct Edge {
	int u, v, to;
	ll f, cap;
	Edge *twin;
};
 
vector <Edge> g[N];
vector <Edge*> h[N];
 
ll S, T, n, m;
Edge* p[N];
 
bool dfs (ll x) {
	if (x == T) return true;
	while (h[x].size ()) {
		Edge* to = h[x].back ();
 
		if (to -> f && dfs (to -> v)) {
			p[to -> v] = to;
			return true;
		}
		h[x].pop_back ();
	}
 
	return false;
}
 
ll flow () {
	ll s = 0, a;
 
	while (true) {
		queue <int> q;
		q.push (S);
 
		vector <ll> d (T + 1, INF);
		d[S] = 0;
 
		while (!q.empty ()) {
			ll x = q.front ();
			q.pop ();
 
			for (Edge to : g[x]) {
				if (to.f && d[to.v] > d[to.u] + 1) {
					d[to.v] = d[to.u] + 1;
					q.push (to.v);
				}
			}
		}
 
		for (ll i = 0; i <= T; i++) {
			h[i].clear ();
			for (Edge& to : g[i]) {
				if (d[to.v] == d[to.u] + 1) h[i].push_back (&to);
			}
		}
 
		a = 0;
 
		while (dfs (S)) {
			ll x = T, cap = INF;
 
			while (x != S) {
				cap = min (cap, p[x] -> f);
				x = p[x] -> u;
			}
 
			x = T;
 
			while (x != S) {
				p[x] -> f -= cap;
				p[x] -> twin -> f += cap;
				x = p[x] -> u;
			}
 
			a += cap;
		}
 
		if (!a) return s;
		s += a;
	}
}
 
void add_edge (ll u, ll v, ll f) {
	Edge a {u, v, (int) g[v].size (), f, f};
	Edge b {v, u, (int) g[u].size (), 0, 0};
 
	g[u].push_back (a);
	g[v].push_back (b);
}
 
int a[N];
 
int main () {
	cin >> n >> m;
 
	for (ll i = 1; i <= n; i++) {
		cin >> a[i];
	}
 
	ll sum = 0;
 
	for (ll i = 1; i <= m; i++) {
		ll a, b, w;
		cin >> a >> b >> w;
 
		sum += w;
 
		add_edge (0, i, w);
		add_edge (i, m + a, INF);
		add_edge (i, m + b, INF);
	}
 
	T = n + m + 1;
 
	for (ll i = 1; i <= n; i++) {
		add_edge (m + i, T, a[i]);
	}
 
	for (ll i = 0; i <= T; i++)
		for (Edge& to : g[i])
			to.twin = &g[to.v][to.to];
 
	sum -= flow ();
 
	cout << sum << endl;
}
