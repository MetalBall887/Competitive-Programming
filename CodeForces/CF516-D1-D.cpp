#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
//Let's observe some properties of the center of the diameter. Let's say di is the length of the longest path starting at i. Then, center of the diagonal has 
//the lowest di and the more you "go away" from the center, the larger di is. That means, if we root the tree in the center, the longest distance from a vertex
//is at least the longest distance from its parent. That means if we take the subtree rooted in x and from the subtree take all vertices with di >= dx - L, these
//vertices will form a connected subgraph. So for each L we should for each x count the number of vertices in its subtree that have distance from the farthest leaf
//>= dx - L. It can be done by sorting by di, doing sliding window method, where the window is a BIT that we use to answer to subtree queries.
 
using namespace __gnu_pbds;
 
#define N 2000003
 
using namespace std;
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
 
const ll INF = 1e18, MOD = 1e9 + 7, MOD2 = 1e6 + 3;
 
vector < pair <ll, ll> > g[N];
 
ll n, r, tin[N], tout[N], timer, d[N], q;
 
struct BIT {
	ll t[N];
 
	void update (ll x, ll d) {
		for (; x <= n; x = (x | (x + 1)))
			t[x] += d;
	}
 
	ll get (ll r) {
		ll sum = 0;
 
		for (; r >= 0; r = (r & (r + 1)) - 1)
			sum += t[r];
 
		return sum;
	}
 
	ll get (ll l, ll r) {
		return get (r) - get (l - 1);
	}
} t;
 
pair <ll, ll> dfs (ll x, ll p = -1, ll h = 0) {
	pair <ll, ll> mx {h, x};
 
	d[x] = max (d[x], h);
 
	for (auto to : g[x]) {
		if (to.first == p) continue;
		mx = max (mx, dfs (to.first, x, h + to.second));
	}
 
	return mx;
}
 
void precalc (ll x, ll p = -1) {
	tin[x] = ++timer;
 
	for (auto to : g[x]) {
		if (to.first == p) continue;
		precalc (to.first, x);
	}
 
	tout[x] = timer;
}
 
ll find_center () {
	dfs (dfs (dfs (0).second).second);
 
	for (ll i = 0; i < n; i++) {
		if (d[r] > d[i]) r = i;
	}
 
	precalc (r);
}
 
int main () {
	ios::sync_with_stdio(0);
	cin.tie(0);
 
	cin >> n;
 
	for (ll i = 0; i < n - 1; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
 
		g[a-1].emplace_back (b - 1, c);
		g[b-1].emplace_back (a - 1, c);
	}
 
	find_center ();
 
	vector <ll> s (n);
 
	for (ll i = 0; i < n; i++) {
		s[i] = i;
	}
 
	sort (s.begin(), s.end(), [&] (ll i, ll j) { return tie (d[i], tin[i]) < tie (d[j], tin[j]); });
 
	cin >> q;
 
	for (ll i = 0; i < q; i++) {
		ll l, j = 0, ans = 0;
		cin >> l;
 
		for (ll i = 0; i < n; i++) {
			while (j < n && d[s[j]] - l <= d[s[i]]) {
				t.update (tin[s[j]], 1);
				j++;
			}
 
			ans = max (ans, t.get (tin[s[i]], tout[s[i]]));
 
			t.update (tin[s[i]], -1);
		}
 
		cout << ans << endl;
	}
}
