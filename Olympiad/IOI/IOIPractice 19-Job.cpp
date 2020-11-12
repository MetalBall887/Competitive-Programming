#include "job.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//First we should notice that if there is no tree condition, if job i is done right before job j, if we swap them, the overall price will change to ui*dj-di*uj
//if ui/di < uj/dj, this value is negative, so we can swap them. With this invariant we can show that it's optimal to sort jobs by decreasing of ui/di. Also
//the corollary is, if there is a job with the highest ui/di, it's always optimal to do it first. Now with the tree condition: if x is the job with the highest
//ui/di, then, once its parent will be done, it will be optimal to do this job immediately, so this job is done right after its parent and we can "merge" these
//two jobs. u of new job is u1+u2, d is d1+d2, except when we need the cost to do this job alone will not be (u1+u2)*(d1+d2) but u1*d1 + u2*(d1+d2), so we need to
//subtract u2*d1 beforehand
 
using namespace __gnu_pbds;
 
#define N 2000001
 
using namespace std;
 
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
int merged[N], dsu[N], n, dl[N];
ll ans;
 
struct rat {
	ll u, d;
 
	rat (ll u, ll d) : u (u), d (d) {}
	rat () {}
 
	bool operator < (const rat& b) const {
		return b.u * d > u * b.d;
	}
 
	bool operator != (const rat& b) const {
		return tie (u, d) != tie (b.u, b.d);
	}
} a[N];
 
int find (int x) {
	if (dsu[x] == x) return x;
	return dsu[x] = find (dsu[x]);
}
 
void unite (int a, int b) {
	a = find (a), b = find (b);
	if (a == b) return;
	dsu[b] = a;
	merged[b] = 1;
}
 
ll scheduling_cost (vector <int> p, vector <int> u, vector <int> d) {
	int n = p.size ();
	
	p.resize (n);
	u.resize (n);
	d.resize (n);
	
	priority_queue < pair <rat, int> > q;
 
	for (int i = 0; i < n; i++) {
		a[i] = {u[i], d[i]};
		dsu[i] = i;
		q.push ({a[i], i});
	}
 
	ll t = 0;
 
	while (!q.empty ()) {
		ll x = q.top ().second;
		rat cost = q.top ().first;
		q.pop ();
		if (a[x] != cost || merged[x] || dl[x]) continue;
 
		if (p[x] == -1 || dl[find (p[x])]) {
			ans += (d[x] + t) * u[x];
			dl[x] = 1;
			t += d[x];
			continue;
		}
		int desc = find (p[x]);
		ans -= (ll) d[x] * u[desc];
		u[desc] += u[x];
		d[desc] += d[x];
		a[desc] = {u[desc], d[desc]};
		unite (desc, x);
 
		q.push ({a[desc], desc});
	}
 
	return ans;
}
