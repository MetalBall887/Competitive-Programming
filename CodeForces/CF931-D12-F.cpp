#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//On a line instead of tree this problem can be solved with Convex Hull trick: starting from the end we keep a line container, where each line represents a linear
//function b[i]*x + dp[i] where dp[i] - the answer for a segment [i..n]. For a tree type we start from leaves: dp[x] - the answer for a subtree rooted at x.
//Everything is the same except when we are calculating dp for a subtree x, we have to consider all child line containers at once, for that we merge them from
//small to large.
 
//using namespace __gnu_pbds;
 
#define N 100000
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
const int M = 1e6;

int n, a[N], b[N], x;
ll ans[N], mode;

vector <int> g[N];

struct line {
	ll k, b;
	ld left;
	bool is_query;
	bool operator < (const line& r) const { 
		if (r.is_query || is_query) return left < r.left;
		if (k == r.k) return b < r.b;
		return k > r.k;
	}

	ld intersect (line r) {
		return (ld) (r.b - b) / (k - r.k);
	}
};

struct CHT {
	set <line> s;

	bool bad (line a, line b, line c) {
		return a.intersect (b) >= b.intersect (c);
	}

	bool bad (set <line> :: iterator it) {
		if (it == s.begin () || next (it) == s.end ()) return false;
		return bad (*prev (it), *it, *next (it));
	}

	void update (set <line> :: iterator it) {
		if (it == s.end ()) return;
		line a = *it;
		if (it == s.begin ()) a.left = -INF;
		else a.left = a.intersect (*prev (it));
		s.erase (it);
		s.insert (a);
	}

	void add (ll k, ll b) {
		line x {k, -INF, 0, false};

		auto it = s.lower_bound (x);
		if (it != s.end () && it -> k == x.k) {
			if (it -> b <= b) return;
			else s.erase (it);
		}

		x.b = b;
		it = s.insert (x).first;
		if (bad (it)) { s.erase (it); return; }

		if (it != s.begin ()) while (bad (prev (it))) s.erase (prev (it));
		if (next (it) != s.end ()) while (bad (next (it))) s.erase (next (it));

		update (it);
		update (++it);
	}

	ll find (int x) {
		line a {0, 0, (ld) x, true};

		auto it = s.lower_bound (a);
		it--;
		return it -> k * x + it -> b;
	}
} d[N];

int p[N], sz[N];

int find (int x) {
	if (p[x] == x) return x;
	return p[x] = find (p[x]);
}

void unite (int a, int b) {
	a = find (a), b = find (b);

	if (a == b) return;
	if (sz[a] < sz[b]) swap (a, b);

	p[b] = a;
	sz[a] += sz[b];

	for (auto l : d[b].s) {
		d[a].add (l.k, l.b);
	}

	d[b].s.clear ();
}

int ptr = 0;

void dfs (int x, int up) {
	sz[x] = 1;
	p[x] = x;

	int ch = -1;

	for (int to : g[x]) {
		if (to == up) continue;
		dfs (to, x);
		if (ch != -1) unite (ch, to);
		ch = to;
	}

	if (ch == -1) {
		d[x].add (b[x], 0);

		return;
	}

	ch = find (ch);
	ans[x] = d[ch].find (a[x]);

	d[x].add (b[x], ans[x]);
	unite (x, ch);
}

signed main () {
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> a[i];
		//a[i] = rand () % 100000;
	}

	for (int i = 0; i < n; i++) {
		cin >> b[i];
		//b[i] = rand () % 100000;
	}

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		//a = i, b = i + 1;

		g[a].push_back (b);
		g[b].push_back (a);
	}

	dfs (0, -1);

	for (int i = 0; i < n; i++)
		cout << ans[i] << ' ';
}
